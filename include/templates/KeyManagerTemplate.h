#pragma once

auto KEYMANAGER_H_TEMPLATE { R"(#pragma once

namespace be {

using Key = unsigned int;
class KeyManager {
public:
	static KeyManager &getInstance();
	
	bool isKeyPressed(Key key) const;
	bool isKeyDown(Key key) const;
	bool isKeyReleased(Key key) const;
private:
	template<typename T>
	friend class Game;
	
	class KeyMap {
	public:
		static constexpr int CacheLineSize { 64 };
		static constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };
		
		void operator=(const KeyMap &other);
		void insert(Key key);
		bool contains(Key key) const;
		void remove(Key key);
	private:
		Key m_keys[ArraySize];
		unsigned char m_size { 0 };
	};
	
	KeyManager() = default;
	~KeyManager() = default;
	
	void update();
	
	void keyPressed(Key key);
	void keyReleased(Key key);
	
	KeyMap m_currFrameKeys;
	KeyMap m_oldFrameKeys;
};

} // namespace be
)" };

auto KEYMANAGER_CPP_TEMPLATE { R"(#include "be/KeyManager.h"

namespace be {

KeyManager &KeyManager::getInstance() {
	static KeyManager instance;
	return instance;
}

bool KeyManager::isKeyPressed(Key key) const { return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key); }
bool KeyManager::isKeyDown(Key key) const { return m_currFrameKeys.contains(key); }
bool KeyManager::isKeyReleased(Key key) const { return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key); }

void KeyManager::update() { m_oldFrameKeys = m_currFrameKeys; }

void KeyManager::keyPressed(Key key) { m_currFrameKeys.insert(key); }
void KeyManager::keyReleased(Key key) { m_currFrameKeys.remove(key); }

void KeyManager::KeyMap::operator=(const KeyManager::KeyMap &other) {
	m_size = other.m_size;
	for(unsigned char i = 0; i < m_size; ++i) m_keys[i] = other.m_keys[i];
}

void KeyManager::KeyMap::insert(Key key) {
	if(!contains(key) && m_size < KeyManager::KeyMap::ArraySize) m_keys[m_size++] = key;
}

void KeyManager::KeyMap::remove(Key key) {
	for(unsigned char i = 0; i < m_size; ++i) {
		if(m_keys[i] == key) {
			m_keys[i] = m_keys[--m_size];
			return;
		}
	}
}

bool KeyManager::KeyMap::contains(Key key) const {
	for(unsigned char i = 0; i < m_size; ++i) if(m_keys[i] == key) return true;
	return false;
}

} // namespace be
)" };
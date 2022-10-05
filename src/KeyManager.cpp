#include "KeyManager.h"
#include "utils/Class.h"
#include "utils/ForStatement.h"
#include "utils/IfStatement.h"
#include "utils/Instruction.h"
#include "utils/Function.h"
#include "utils/Namespace.h"
#include "utils/File.h"

namespace gbg::generators {

void KeyManager::generate() const
{
	generateHeader();
	generateSource();
}

void KeyManager::generateHeader() const
{
	File("include/be/KeyManager.h", {
		"#pragma once"
		"",
	}, {
		Namespace("BE", {
			"using Key = unsigned int;"
			"",
			Class("KeyManager", {
				"static KeyManager &getInstance();",
				"",
				"bool isKeyPressed(Key key) const;",
				"bool isKeyDown(Key key) const;",
				"bool isKeyReleased(Key key) const;"
			}, {}, {
				"template<typename T>",
				"friend class Game;",
				"",
				Class("KeyMap", {
					"static constexpr int CacheLineSize { 64 };",
					"static constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };",
					"",
					"void operator=(const KeyMap &other);",
					"void insert(Key key);",
					"bool contains(Key key) const;",
					"void remove(Key key);"
				}, {}, {
					"Key m_keys[ArraySize];",
					"unsigned char m_size { 0 };"
				}),
				"",
				"KeyManager() = default;",
				"~KeyManager() = default;",
				"",
				"void update();",
				"",
				"void keyPressed(Key key);",
				"void keyReleased(Key key);",
				"",
				"KeyMap m_currFrameKeys;",
				"KeyMap m_oldFrameKeys;"
			})
		})
	}).write();
}

void KeyManager::generateSource() const
{
	File("src/KeyManager.cpp", { "#include \"be/KeyManager.h\"" }, {
		Namespace("BE", {
			Function("", "KeyManager &KeyManager::getInstance()", {
				"static KeyManager instance;",
				"return instance;"
			}),
			"",
			"bool KeyManager::isKeyPressed(Key key) const { return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key); }",
			"bool KeyManager::isKeyDown(Key key) const { return m_currFrameKeys.contains(key); }",
			"bool KeyManager::isKeyReleased(Key key) const { return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key); }",
			"",
			"void KeyManager::update() { m_oldFrameKeys = m_currFrameKeys; }",
			"",
			"void KeyManager::keyPressed(Key key) { m_currFrameKeys.insert(key); }",
			"void KeyManager::keyReleased(Key key) { m_currFrameKeys.remove(key); }",
			"",
			Function("", "void KeyManager::KeyMap::operator=(const KeyManager::KeyMap &other)", {
				"m_size = other.m_size;",
				"for(unsigned char i = 0; i < m_size; ++i) m_keys[i] = other.m_keys[i];"
			}),
			"",
			Function("", "void KeyManager::KeyMap::insert(Key key)", {
				"if(!contains(key) && m_size < KeyManager::KeyMap::ArraySize) m_keys[m_size++] = key;"
			}),
			"",
			Function("", "void KeyManager::KeyMap::remove(Key key)", {
				ForStatement("unsigned char i = 0", "i < m_size", "++i", { IfStatement("m_keys[i] == key", { "m_keys[i] = m_keys[--m_size];", "return;" }) })
			}),
			"",
			Function("", "bool KeyManager::KeyMap::contains(Key key) const", {
				"for(unsigned char i = 0; i < m_size; ++i) if(m_keys[i] == key) return true;",
				"return false;"
			})
		})
	}).write();
}

}

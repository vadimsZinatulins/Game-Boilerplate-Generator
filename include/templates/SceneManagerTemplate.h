#pragma once

auto SCENEMANAGER_H_TEMPLATE { R"(#pragma once

#include "IScene.h"

#include <stack>
#include <vector>

namespace be {

class SceneManager {
public:
	static SceneManager &getInstance();
	
	template<typename T>
	void pushScene() {
		m_scenesToAdd.push_back(new T());
	}
	
	template<typename T>
	void swap() {
		popScene();
		pushScene<T>();
	}
	
	void popScene();
	void popAllScenes();
private:
	template<typename T>
	friend class Game;
	
	SceneManager() = default;
	~SceneManager() = default;
	
	void updateState(const IScene::InitializationParams &params);
	
	IScene *getActiveScene() const;
	
	std::stack<IScene*> m_scenes;
	
	std::vector<IScene*> m_scenesToAdd;
	std::vector<IScene*> m_scenesToFree;
};

} // namespace be
)" };

auto SCENEMANAGER_CPP_TEMPLATE { R"(#include "be/SceneManager.h"

namespace be {

SceneManager &SceneManager::getInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::popScene() {
	if(m_scenes.size()) {
		m_scenesToFree.push_back(m_scenes.top());
		m_scenes.pop();
	}
}

void SceneManager::popAllScenes() {
	while(m_scenes.size()) {
		m_scenesToFree.push_back(m_scenes.top());
		m_scenes.pop();
	}
}

IScene *SceneManager::getActiveScene() const {
	if(m_scenes.size()) return m_scenes.top();
	return nullptr;
}

void SceneManager::updateState(const IScene::InitializationParams &params) {
	for(IScene *scene : m_scenesToAdd) {
		scene->initialize(params);
		m_scenes.push(scene);
	}
	
	for(IScene *scene : m_scenesToFree) {
		scene->shutdown(params);
		delete scene;
	}
	
	m_scenesToAdd.clear();
	m_scenesToFree.clear();
}

} // namespace be
)" };
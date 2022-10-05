#include "SceneManager.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/ForStatement.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"
#include "utils/WhileStatement.h"

namespace gbg::generators {

void SceneManager::generate() const {
	generateSceneManagerHeader();
	generateSceneManagerSource();

	generateSceneHeader();

	generateMainMenuSceneHeader();
	generateMainMenuSceneSource();
}

void SceneManager::generateSceneManagerHeader() const {
	File("include/be/SceneManager.h", {
		"#pragma once",
		"",
		"#include \"IScene.h\"",
		"",
		"#include <stack>",
		"#include <vector>",
	}, {
		Namespace("be", {
			Class("SceneManager", {
				"static SceneManager &getInstance();",
				"",
				Function("template<typename T>", "void pushScene()", {
					"m_scenesToAdd.push_back(new T());"
				}),
				"",
				Function("template<typename T>", "void swap()", {
					"popScene();",
					"pushScene<T>();"
				}),
				"",
				"void popScene();",
				"void popAllScenes();"
			}, {}, {
				"template<typename T>",
				"friend class Game;",
				"",
				"SceneManager() = default;",
				"~SceneManager() = default;",
				"",
				"void updateState();",
				"",
				"IScene *getActiveScene() const;",
				"",
				"std::stack<IScene*> m_scenes;",
				"",
				"std::vector<IScene*> m_scenesToAdd;",
				"std::vector<IScene*> m_scenesToFree;"
			})
		})
	}).write();
}

void SceneManager::generateSceneManagerSource() const {
	File("src/be/SceneManager.cpp", { "#include \"be/SceneManager.h\"", "" }, {
		Namespace("be", {
			Function("", "SceneManager &SceneManager::getInstance()", {
				"static SceneManager instance;",
				"return instance;"
			}),
			"",
			Function("", "void SceneManager::popScene()", {
				IfStatement("m_scenes.size()", {
					"m_scenesToFree.push_back(m_scenes.top());",
					"m_scenes.pop();"
				})
			}),
			"",
			Function("", "void SceneManager::popAllScenes()", {
				WhileStatement("m_scenes.size()", {
					"m_scenesToFree.push_back(m_scenes.top());",
					"m_scenes.pop();"
				})
			}),
			"",
			Function("", "IScene *SceneManager::getActiveScene() const", {
				"if(m_scenes.size()) return m_scenes.top();",
				"return nullptr;"
			}),
			"",
			Function("", "void SceneManager::updateState()", {
				ForStatement("IScene *scene : m_scenesToAdd", {
					"scene->initialize();",
					"m_scenes.push(scene);"
				}),
				"",
				ForStatement("IScene *scene : m_scenesToFree", {
					"scene->shutdown();",
					"delete scene;"
				}),
				"",
				"m_scenesToAdd.clear();",
				"m_scenesToFree.clear();"
			})
		})
	}).write();
}


void SceneManager::generateSceneHeader() const
{
	File("include/be/IScene.h", { 
		"#pragma once", 
		"", 
		"struct SDL_Renderer;",
	}, {
		Namespace("be", {
			Class("IScene", {
				"IScene() = default;",
				"virtual ~IScene() = default;",
				"",
				"virtual void initialize() = 0;",
				"virtual void shutdown() = 0;",
				"",
				"virtual void update() = 0;",
				"virtual void render(SDL_Renderer *renderer) = 0;"
			}, {}, {})
		})
	}).write();
}

void SceneManager::generateMainMenuSceneHeader() const
{
	File("include/MainMenuScene.h", {
		"#pragma once",
		"",
		"#include \"be/IScene.h\"",
	}, {
		Class("MainMenuScene : public be::IScene", {
			"void initialize() override;",
			"void shutdown() override;",
			"",
			"void update() override;",
			"void render(SDL_Renderer *renderer) override;"
		}, {}, {})
	}).write();
}

void SceneManager::generateMainMenuSceneSource() const
{
	File("src/MainMenuScene.cpp", {
		"#include \"MainMenuScene.h\"",
		"",
		"#include <SDL2/SDL.h>"
	}, {
		Function("", "void MainMenuScene::initialize()", { "" }),
		"",
		Function("", "void MainMenuScene::shutdown()", { "" }),
		"",
		Function("", "void MainMenuScene::update()", { "" }),
		"",
		Function("", "void MainMenuScene::render(SDL_Renderer *renderer)", { "" })
	}).write();
}

}

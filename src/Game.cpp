#include "Game.h"
#include "utils/Case.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"
#include "utils/SwitchStatement.h"
#include "utils/WhileStatement.h"

#include <sstream>

namespace gbg::generators {

void Game::generate() const {
	generateHeader();
}

void Game::setWithSDL2ImageExtra(bool flag) {
	m_withSDL2ImageExtra = flag;
}

void Game::generateHeader() const {
	std::stringstream sdl2ImageInclude;
	std::stringstream sdl2ImageTextureInclude;
	std::stringstream sdl2ImageTextureInit;
	std::stringstream sdl2ImageTextureClear;
	std::stringstream sdl2ImageInit;
	std::stringstream sdl2ImageQuit;

	if(m_withSDL2ImageExtra) {
		sdl2ImageTextureInclude << "#include \"be/TextureManager.h\"";
		sdl2ImageTextureClear << "TextureManager::getInstance().clear();";
		sdl2ImageTextureInit << "TextureManager::getInstance().init(m_renderer);";
		sdl2ImageInclude << "#include <SDL_image.h>";
		sdl2ImageInit << "IMG_Init(IMAGE_INIT);";
		sdl2ImageQuit << "IMG_Quit();";
	}

	File("include/be/Game.h", {
		"#pragma once",
		sdl2ImageTextureInclude.str(),
		"#include \"be/Time.h\"\n",
		"#include \"be/KeyManager.h\"",
		"#include \"be/MouseManager.h\"",
		"#include \"be/SceneManager.h\"",
		"",
		"#include \"config.h\"",
		"",
		"#include <SDL.h>",
		sdl2ImageInclude.str()
	}, {
		Namespace("be", {
			"template<typename T>",
			Class("Game", {
				"Game() = default;",
				"~Game() = default;",
				"",
				Function("", "void run()", {
					"init();",
					"loop();",
					"close();"
				}),
				"",
			}, {}, {
				Function("", "void init()", {
					"SDL_Init(SDL_INIT_VIDEO);",
					sdl2ImageInit.str(),
					"",
					"m_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);",
					"m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);",
					"",
					sdl2ImageTextureInit.str(),
					"",
					"SDL_SetRenderDrawColor(m_renderer, 0x00f, 0x00f, 0x00f, 0xff);",
					"",
					"static_cast<T*>(this)->initialize();",
					"",
					"SceneManager::getInstance().updateState();"
				}),
				"",
				Function("", "void loop()", {
					"auto &keys = KeyManager::getInstance();",
					"auto &mouse = MouseManager::getInstance();",
					"auto &scenes = SceneManager::getInstance();",
					"",
					"SDL_Event e;",
					"",
					WhileStatement("IScene *scene = scenes.getActiveScene()", {
						"Time frameTimer;",
						"",
						"keys.update();",
						"mouse.update();",
						"",
						WhileStatement("SDL_PollEvent(&e)", {
							SwitchStatement("e.type", {
								Case("SDL_QUIT", { "scenes.popAllScenes();" }), "",
								Case("SDL_KEYDOWN", { "keys.keyPressed(e.key.keysym.sym);" }), "",
								Case("SDL_KEYUP", { "keys.keyReleased(e.key.keysym.sym);" }), "",
								Case("SDL_MOUSEBUTTONDOWN", { "mouse.buttonPressed(static_cast<MouseButton>(e.button.button));" }), "",
								Case("SDL_MOUSEBUTTONUP", { "mouse.buttonReleased(static_cast<MouseButton>(e.button.button));" }), "",
								Case("SDL_MOUSEMOTION", { "mouse.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);" }), ""
							}), ""
						}),
						"",
						"scene->update();",
						"",
						"SDL_RenderClear(m_renderer);",
						"scene->render(m_renderer);",
						"SDL_RenderPresent(m_renderer);"
					}),
					"",
					sdl2ImageTextureClear.str()
				}),
				"",
				Function("", "void close()", {
					"static_cast<T*>(this)->shutdown();",
					"",
					IfStatement("m_renderer", {
						"SDL_DestroyRenderer(m_renderer);",
						"m_renderer = nullptr;"
					}),
					"",
					IfStatement("m_window", {
						"SDL_DestroyWindow(m_window);",
						"m_window = nullptr;"
					}),
					"",
					sdl2ImageQuit.str(),
					"SDL_Quit();"
				}),
				"",
				"SDL_Window *m_window { nullptr };",
				"SDL_Renderer *m_renderer { nullptr };"
			})
		})
	}).write();
}

}

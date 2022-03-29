#include "Game.h"
#include "utils/Case.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"
#include "utils/SwitchStatement.h"
#include "utils/WhileStatement.h"

void Game::generate() const
{
	generateHeader();
}

void Game::generateHeader() const
{
	File("include/BE/" + m_className + ".h", {
		"#pragma once",
		"",
		"#include \"BE/Time.h\"\n",
		"#include \"BE/KeyManager.h\"",
		"#include \"BE/MouseManager.h\"",
		"#include \"BE/SceneManager.h\"",
		"#include \"BE/TextureManager.h\"",
		"#include \"config.h\"",
		"",
		"#include <SDL2/SDL.h>",
		"#include <SDL2/SDL_image.h>"
	}, {
		Namespace("BE", {
			"template<typename T>",
			Class(m_className, {
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
					"IMG_Init(IMAGE_INIT);",
					"",
					"m_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);",
					"m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);",
					"",
					"TextureManager::getInstance().init(m_renderer);",
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
					"TextureManager::getInstance().clear();"
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
					"SDL_Quit();"
				}),
				"",
				"SDL_Window *m_window { nullptr };",
				"SDL_Renderer *m_renderer { nullptr };"
			})
		})
	}).write();
}


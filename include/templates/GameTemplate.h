#pragma once

auto GAME_H_TEMPLATE { R"(#pragma once

#include "be/Time.h"
#include "be/KeyManager.h"
#include "be/MouseManager.h"
#include "be/SceneManager.h"

#include "config.h"

#include <SDL3/SDL.h>

namespace be {

template<typename T>
class Game {
public:
	Game() = default;
	~Game() = default;
	
	void run() {
		init();
		loop();
		close();
	}
	
private:
	void init() {
		SDL_Init(SDL_INIT_VIDEO);
		
		m_window = SDL_CreateWindow(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		m_renderer = SDL_CreateRenderer(m_window, nullptr);
		
		SDL_SetRenderDrawColor(m_renderer, 0x00f, 0x00f, 0x00f, 0xff);
		
		static_cast<T*>(this)->initialize();
		
		SceneManager::getInstance().updateState({ m_renderer });
	}
	
	void loop() {
		auto &keys = KeyManager::getInstance();
		auto &mouse = MouseManager::getInstance();
		auto &scenes = SceneManager::getInstance();
		
		const auto initParams = IScene::InitializationParams { m_renderer };

		SDL_Event e;
		
		while(IScene *scene = scenes.getActiveScene()) {
			Time frameTimer;
			
			keys.update();
			mouse.update();
			
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
				case SDL_EVENT_QUIT:
					scenes.popAllScenes();
					break;				
				case SDL_EVENT_KEY_DOWN:
					keys.keyPressed(e.key.key);
					break;				
				case SDL_EVENT_KEY_UP:
					keys.keyReleased(e.key.key);
					break;				
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					mouse.buttonPressed(static_cast<MouseButton>(e.button.button));
					break;				
				case SDL_EVENT_MOUSE_BUTTON_UP:
					mouse.buttonReleased(static_cast<MouseButton>(e.button.button));
					break;				
				case SDL_EVENT_MOUSE_MOTION:
					mouse.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
					break;				
				}				
			}
			
			scene->update();
			
			SDL_RenderClear(m_renderer);
			scene->render(m_renderer);
			SDL_RenderPresent(m_renderer);

			scenes.updateState(initParams);
		}
	}
	
	void close() {
		static_cast<T*>(this)->shutdown();
		
		if(m_renderer) {
			SDL_DestroyRenderer(m_renderer);
			m_renderer = nullptr;
		}
		
		if(m_window) {
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}
		
		SDL_Quit();
	}
	
	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
};

} // namespace be
)" };

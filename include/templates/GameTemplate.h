#pragma once

auto GAME_H_TEMPLATE { R"(#pragma once

#include "be/Time.h"
#include "be/KeyManager.h"
#include "be/MouseManager.h"
#include "be/SceneManager.h"{TEXTURE_MANAGER_INCLUDE}

#include "config.h"

#include <SDL.h>{SDL_IMAGE_INCLUDE}

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
		SDL_Init(SDL_INIT_VIDEO);{IMG_INIT}
		
		m_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);{TEXTURE_MANAGER_INIT}
		
		SDL_SetRenderDrawColor(m_renderer, 0x00f, 0x00f, 0x00f, 0xff);
		
		static_cast<T*>(this)->initialize();
		
		SceneManager::getInstance().updateState();
	}
	
	void loop() {
		auto &keys = KeyManager::getInstance();
		auto &mouse = MouseManager::getInstance();
		auto &scenes = SceneManager::getInstance();
		
		SDL_Event e;
		
		while(IScene *scene = scenes.getActiveScene()) {
			Time frameTimer;
			
			keys.update();
			mouse.update();
			
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
				case SDL_QUIT:
					scenes.popAllScenes();
					break;				
				case SDL_KEYDOWN:
					keys.keyPressed(e.key.keysym.sym);
					break;				
				case SDL_KEYUP:
					keys.keyReleased(e.key.keysym.sym);
					break;				
				case SDL_MOUSEBUTTONDOWN:
					mouse.buttonPressed(static_cast<MouseButton>(e.button.button));
					break;				
				case SDL_MOUSEBUTTONUP:
					mouse.buttonReleased(static_cast<MouseButton>(e.button.button));
					break;				
				case SDL_MOUSEMOTION:
					mouse.mouseMoved(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
					break;				
				}				
			}
			
			scene->update();
			
			SDL_RenderClear(m_renderer);
			scene->render(m_renderer);
			SDL_RenderPresent(m_renderer);
		}{TEXTURE_MANAGER_CLEAR}
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
		
        {IMG_QUIT}SDL_Quit();
	}
	
	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
};

} // namespace be
)" };

auto GAME_TEXTURE_MANAGER_INCLUDE_TEMPLATE { R"(
#include "be/TextureManager.h")" 
};

auto GAME_SDL_IMAGE_INCLUDE_TEMPLATE { R"(
#include <SDL_image.h>)" 
};

auto GAME_IMG_INIT_TEMPLATE { R"(
        IMG_Init(IMAGE_INIT);)" 
};

auto GAME_TEXTURE_MANAGER_INIT_TEMPLATE { R"(
		TextureManager::getInstance().init(m_renderer);)" 
};

auto GAME_TEXTURE_MANAGER_CLEAR_TEMPLATE { R"(
		TextureManager::getInstance().clear();)" 
};

auto GAME_IMG_QUIT_TEMPLATE { R"(IMG_Quit();
        )" 
};

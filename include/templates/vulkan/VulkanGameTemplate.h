#pragma once

const auto VULKAN_GAME_H_TEMPLATE { R"(#pragma once

#include "be/Time.h"
#include "be/KeyManager.h"
#include "be/MouseManager.h"
#include "be/SceneManager.h"
#include "be/vulkan/Instance.h"
#include "be/vulkan/DebugMessenger.h"

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
		
		m_window = SDL_CreateWindow(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
		
		bool enableDebug { true };
		m_vulkanInstance = std::make_shared<vulkan::Instance>(m_window, enableDebug);
		if(enableDebug) {
			m_vulakDebug = std::make_shared<vulkan::DebugMessenger>(m_vulkanInstance);
		}

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
			
			scene->render();
		}
	}
	
	void close() {
		static_cast<T*>(this)->shutdown();

		m_vulakDebug.reset();
		m_vulkanInstance.reset();
		
		if(m_window) {
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}
		
        SDL_Quit();
	}
	
	SDL_Window *m_window { nullptr };

	vulkan::Instance::Ptr m_vulkanInstance { nullptr };
	vulkan::DebugMessenger::Ptr m_vulakDebug { nullptr };
};

} // namespace be
)" };

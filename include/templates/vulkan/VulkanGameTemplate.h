#pragma once

const auto VULKAN_GAME_H_TEMPLATE { R"(#pragma once

#include "Time.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "vulkan/Instance.h"
#include "vulkan/DebugMessenger.h"
#include "vulkan/Surface.h"
#include "vulkan/PhysicalDevice.h"
#include "vulkan/Device.h"
#include "vulkan/Swapchain.h"
#include "vulkan/ShaderModule.h"
#include "vulkan/Pipeline.h"

#include "vulkan/device_picker/DevicePicker.h"
#include "vulkan/device_picker/BaseCriteria.h"
#include "vulkan/device_picker/ExtensionCriteria.h"
#include "vulkan/device_picker/QueueCriteria.h"

#include "config.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_messagebox.h>
#include <stdexcept>

namespace be {

template<typename T>
class Game {
public:
	Game() = default;
	~Game() = default;

	void run() {
		if(init()) {
			loop();
		}
		close();
	}
	
private:
	bool init() {
		if(SDL_Init(SDL_INIT_VIDEO) != 0) {
			return false;
		}
		
		m_window = SDL_CreateWindow(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_VULKAN);
		
		if(!initVulkan()) {
			return false;
		}

		static_cast<T*>(this)->initialize();
		
		SceneManager::getInstance().updateState();

		return true;
	}

	bool initVulkan() {
		bool enableDebug { true };
		try {
			m_instance = std::make_shared<vulkan::Instance>(m_window, enableDebug);

			if(enableDebug) {
				m_debugMessenger = std::make_shared<vulkan::DebugMessenger>(m_instance);
			}

			m_surface = std::make_shared<vulkan::Surface>(m_window, m_instance);

			std::vector<const char *> requiredExtensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			auto devicePicker { 
				vulkan::device_picker::DevicePicker()
					.addCriteria(std::make_shared<vulkan::device_picker::BaseCriteria>())
					.addCriteria(std::make_shared<vulkan::device_picker::ExtensionCriteria>(requiredExtensions))
					.addCriteria(std::make_shared<vulkan::device_picker::QueueCriteria>(m_surface))
			};

			auto physicalDevice {
				devicePicker.pickDevice(
					vulkan::PhysicalDevice::enumeratePhysicalDevices(m_instance)
				)
			};

			if(!physicalDevice.has_value()) {
				throw std::runtime_error("No suitable physical device found");
			}

			m_device = std::make_shared<vulkan::Device>(m_instance, m_surface, physicalDevice.value(), requiredExtensions);
			m_swapchain = std::make_shared<vulkan::Swapchain>(m_window, m_device, m_surface);

			auto vertShader { std::make_shared<vulkan::ShaderModule>("resources/shaders/vertex.spv", m_device) };
			auto fragShader { std::make_shared<vulkan::ShaderModule>("resources/shaders/fragment.spv", m_device) };

			m_pipeline = std::make_shared<vulkan::Pipeline>(m_device, m_swapchain, vertShader, fragShader);
		} catch(const std::exception &e) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Vulkan initialization error", e.what(), m_window);

			return false;
		}

		return true;
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
		
		m_pipeline.reset();
		m_swapchain.reset();
		m_device.reset();
		m_surface.reset();
		m_debugMessenger.reset();
		m_instance.reset();
		
		if(m_window) {
			SDL_DestroyWindow(m_window);
			m_window = nullptr;
		}
		
        SDL_Quit();
	}
	
	SDL_Window *m_window { nullptr };

	vulkan::Instance::Ptr m_instance { nullptr };
	vulkan::DebugMessenger::Ptr m_debugMessenger { nullptr };
	vulkan::Surface::Ptr m_surface { nullptr };
	vulkan::Device::Ptr m_device { nullptr };
	vulkan::Swapchain::Ptr m_swapchain { nullptr };
	vulkan::Pipeline::Ptr m_pipeline { nullptr };
};

} // namespace be
)" };

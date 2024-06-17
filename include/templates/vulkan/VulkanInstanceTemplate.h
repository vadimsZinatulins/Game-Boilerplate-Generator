#pragma once

const auto VULKAN_INSTANCE_H_TEMPLATE { R"(#pragma once

#include <SDL.h>
#include <vulkan/vulkan.h>
#include <memory>

namespace be::vulkan {

class Instance {
public:
    using Ptr = std::shared_ptr<Instance>;

    // Constructor/Destructor
    Instance(SDL_Window *window, bool enableDebug);
    ~Instance();

    operator VkInstance() const;
    
private:
	template<typename T>
	friend class Game;

    // Copy Constructor
    Instance(const Instance &other) = delete;

    // Move Constructor
    Instance(Instance &&other) = delete;
    
    // Copy Assignment
    Instance &operator=(const Instance &other) = delete;
    
    // Move Assignment
    Instance &operator=(Instance &&other) = delete;

    VkInstance m_instance { VK_NULL_HANDLE };
};

}
)" };

const auto VULKAN_INSTANCE_CPP_TEMPLATE { R"(#include "be/vulkan/Instance.h"
#include "be/vulkan/Debug.h"

#include <SDL_vulkan.h>
#include <vector>
#include <stdexcept>
#include <vulkan/vk_enum_string_helper.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace be::vulkan {

namespace local_helpers {
    
void checkExtensionsSupport(const std::vector<const char*> &checkExtensions) {
    // Get the extensions properties count
    uint32_t extensionCount { 0 };
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // Get the extensions properties
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // Get the list of all unsupported extensions
    std::vector<std::string> unsupportedExtensions;
    for(const auto &checkExtension : checkExtensions) {
        bool hasExtension { std::any_of(extensions.begin(), extensions.end(), [checkExtension](const auto &extension) {
            return strcmp(checkExtension, extension.extensionName) == 0;
        }) };

        if(!hasExtension) {
            unsupportedExtensions.push_back(checkExtension);
        }
    }

    if(!unsupportedExtensions.empty()) {
        // Lambda that accumulates all unsupported extensions (comma-separated)
        const auto accumulator { [](const std::string &a, const std::string &b){
            return a + ", " + b;
        } };

        // String message that lists all unsupported extensions
        std::string errorMessage {
            "Unsupported Extensions: " + std::accumulate(
                unsupportedExtensions.begin() + 1, 
                unsupportedExtensions.end(), 
                unsupportedExtensions[0], 
                accumulator
            )
        };

        throw std::runtime_error(errorMessage);
    }
}

void checkValidationLayersSupport(const std::vector<const char*> &layers) {
    // Get the layers count
    uint32_t layerCount { 0 };
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    // Get the layers
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    // Get the list of all unsupported layers
    std::vector<std::string> unsupportedLayers;
    for(const auto &checkLayer : layers) {
        bool hasExtension { std::any_of(availableLayers.begin(), availableLayers.end(), [checkLayer](const auto &layer) {
            return strcmp(checkLayer, layer.layerName) == 0;
        }) };

        if(!hasExtension) {
            unsupportedLayers.push_back(checkLayer);
        }
    }

    if(!unsupportedLayers.empty()) {
        // Lambda that accumulates all unsupported layers (comma-separated)
        const auto accumulator { [](const std::string &a, const std::string &b){
            return a + ", " + b;
        } };

        // String message that lists all unsupported layers
        std::string errorMessage {
            "Unsupported Validation Layers: " + std::accumulate(
                unsupportedLayers.begin() + 1, 
                unsupportedLayers.end(), 
                unsupportedLayers[0], 
                accumulator
            )
        };

        throw std::runtime_error(errorMessage);
    }
}

}

Instance::operator VkInstance() const {
    return m_instance;
}

Instance::Instance(SDL_Window *window, bool enableDebug) {
    // General application information
    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // Application information
    appInfo.pApplicationName = "My Vulkan Project";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    // Engine information
    appInfo.pEngineName = "Basic Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    // Vulkan information
    appInfo.apiVersion = VK_API_VERSION_1_1;

    // Get the extensions count
    uint32_t sdlExtensionCount { 0 };
    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, nullptr);

    // Get the extensions
    std::vector<const char*> instanceExtensions(sdlExtensionCount);
    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, instanceExtensions.data());

    // List of validation layers to use
    std::vector<const char*> validationLayers;

    // Setup empty Debug creation information
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};

    if(enableDebug) {
        // Include Debug Utils Extension if debug is enabled
        instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        // Include Khronos' Validation Layer if debug is enabled
        validationLayers.push_back("VK_LAYER_KHRONOS_validation");

        // Populate Debug creation information if debug is enabled
        Debug::populateDebugCreateInfo(debugCreateInfo);
    }
    
    // Make sure all extensions are supported
    local_helpers::checkExtensionsSupport(instanceExtensions);
    // Make sure all validation layers are supported
    local_helpers::checkValidationLayersSupport(validationLayers);

    // Instance creation information
    VkInstanceCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    // Set Extensions
    createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();
    // Set Validation Layers
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
    // Setup the debug information (if it is empty, it will not take any effect)
    createInfo.pNext = &debugCreateInfo;
    
    if(VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create a Vulkan Instance. Error: " + std::string(string_VkResult(result)));
    }
}

Instance::~Instance() {
    if(m_instance) {
        vkDestroyInstance(m_instance, nullptr);
        
        m_instance = VK_NULL_HANDLE;
    }
}

}
)" };

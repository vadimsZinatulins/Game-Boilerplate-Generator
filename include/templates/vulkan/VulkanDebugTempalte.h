#pragma once

const auto VULKAN_DEBUG_H_TEMPLATE { R"(#pragma once

#include "Instance.h"

#include <vulkan/vulkan.h>
#include <memory>

namespace be::vulkan {

class Debug {
public:
    using Ptr = std::shared_ptr<Debug>;

    // Constructor/Destructor
    Debug(Instance::Ptr instance);
    ~Debug();

private:
	template<typename T>
	friend class Game;
    
	friend class Instance;

    // Copy Constructor
    Debug(const Debug &other) = delete;

    // Move Constructor
    Debug(Debug &&other) = delete;
    
    // Copy Assignment
    Debug &operator=(const Debug &other) = delete;
    
    // Move Assignment
    Debug &operator=(Debug &&other) = delete;

    static void populateDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &pDebugInfo);

    Instance::Ptr m_instance { nullptr };
    VkDebugUtilsMessengerEXT m_debugMessenger { VK_NULL_HANDLE };
};

}
)" };

const auto VULKAN_DEBUG_CPP_TEMPLATE { R"(#include "be/vulkan/Debug.h"

#include <vulkan/vk_enum_string_helper.h>
#include <string>
#include <iostream>
#include <stdexcept>

namespace be::vulkan {

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData
) {
    std::cerr << "Validation Layer ["  << pCallbackData->pMessageIdName << "]: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VkResult createDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger
) {
    // Retrieve the function to create Vulkan Debug Messenger
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    // Return error code if the function does not exist
    if(!func) {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    // Invoke the function and return its output
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
}

void destroyDebugUtulsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *pAllocator
) {
    // Retrieve the function to destroy Vulkan Debug Messenger
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    // Invoke the function if it exists
    if(func) {
        func(instance, debugMessenger, pAllocator);
    }
}

void Debug::populateDebugCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &debugInfo) {
    debugInfo = {};

    debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    // Set the message severity to filter for
    debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    // Set the message type to filter for
    debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    // Set the callback to invoke
    debugInfo.pfnUserCallback = debugCallback;
    // Custom data (not used in this case)
    debugInfo.pUserData = nullptr;
}

Debug::Debug(Instance::Ptr instance) : m_instance(instance) {
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    populateDebugCreateInfo(debugCreateInfo);

    if(VkResult result = createDebugUtilsMessengerEXT(*m_instance, &debugCreateInfo, nullptr, &m_debugMessenger); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create a Vulkan Debug Messenger. Error: " + std::string(string_VkResult(result)));
    }
}

Debug::~Debug() {
    if(m_debugMessenger) {
        destroyDebugUtulsMessengerEXT(*m_instance, m_debugMessenger, nullptr);

        m_debugMessenger = VK_NULL_HANDLE;
    }
}

}
)" };

#pragma once

const auto VULKAN_DEVICE_H_TEMPLATE { R"(#pragma once

#include "Instance.h"
#include "Surface.h"
#include "PhysicalDevice.h"

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace be::vulkan {

class Device {
public:
    using Ptr = std::shared_ptr<Device>;

    // Constructor
    Device(Instance::Ptr instance, Surface::Ptr surface, PhysicalDevice physicalDevice, const std::vector<const char *> &requiredExtensions);

    // Destructor
    ~Device();

    operator VkDevice() const noexcept;
    operator VkPhysicalDevice() const noexcept;

    VkQueue getGraphicsQueue() const noexcept;
    VkQueue getPresentationQueue() const noexcept;
private:
    // Copy Constructor
    Device(const Device &other) = delete;

    // Move Constructor
    Device(Device &&other) = delete;
    
    // Copy Assignment
    Device &operator=(const Device &other) = delete;
    
    // Move Assignment
    Device &operator=(Device &&other) = delete;

    VkDevice m_device { VK_NULL_HANDLE };
    VkPhysicalDevice m_physicalDevice { VK_NULL_HANDLE };
    VkQueue m_graphicsQueue { VK_NULL_HANDLE };
    VkQueue m_presentationQueue { VK_NULL_HANDLE };
};

}
)" };

const auto VULKAN_DEVICE_CPP_TEMPLATE { R"(#include "be/vulkan/Device.h"

#include <optional>
#include <vector>
#include <stdexcept>
#include <string>
#include <utility>
#include <algorithm>
#include <set>

namespace be::vulkan {

namespace local_helpers {

bool hasGraphicsSupport(const VkQueueFamilyProperties &queueFamilyProperties) {
    return queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
}

bool hasPresentationSupport(VkPhysicalDevice device, VkSurfaceKHR surface, const VkQueueFamilyProperties &queueFamilyProperties) {
    VkBool32 presentationSupport { false };
    vkGetPhysicalDeviceSurfaceSupportKHR(device, 0, surface, &presentationSupport);

    return presentationSupport;
}

std::pair<uint32_t, uint32_t> getBestGraphicsAndPresentationIndecies(VkPhysicalDevice device, Surface::Ptr surface, const std::vector<VkQueueFamilyProperties> &queueFamilyProperties) {
    std::optional<int> graphicsIndex;
    std::optional<int> presentationIndex;

    for(uint32_t i = 0; i < queueFamilyProperties.size(); ++i) {
        auto hasGraphics { hasGraphicsSupport(queueFamilyProperties[i]) };
        auto hasPresentation { hasPresentationSupport(device, *surface, queueFamilyProperties[i]) };

        if(hasGraphics && hasPresentation) {
            return { i, i };
        }

        if(hasGraphics && !graphicsIndex.has_value()) {
            graphicsIndex = i;
        }

        if(hasPresentation && !presentationIndex.has_value()) {
            presentationIndex = i;
        }
    }

    return { graphicsIndex.value(), presentationIndex.value() };
}

}

Device::Device(Instance::Ptr instance, Surface::Ptr surface, PhysicalDevice physicalDevice, const std::vector<const char *> &requiredExtensions) 
    : m_physicalDevice(physicalDevice) {
    // Get the Graphics and Presentation Queue Family Indices
    auto queueFamilyIndices { 
        local_helpers::getBestGraphicsAndPresentationIndecies(
            physicalDevice, 
            surface, 
            physicalDevice.getQueueFamilyProperties()
        )
    };

    // Get the Unique Queue Families (unique in the sense that there are no duplicates in case the Graphics and Presentation Queue Families are the same)
    std::set<uint32_t> uniqueQueueFamilies = { 
        queueFamilyIndices.first,
        queueFamilyIndices.second
    };

    // Set the Queue Priority for all Queues
    float priority { 1.0f };

    // Create the Queue Create Infos
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    // For each Unique Queue Family, create a Queue Create Info
    for(const auto &queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &priority;

        queueCreateInfos.push_back(queueCreateInfo);
    }

    // Default Device Features
    VkPhysicalDeviceFeatures deviceFeatures {};

    // Create the Device
    VkDeviceCreateInfo deviceCreateInfo {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    if(VkResult result = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Device. Error code: " + std::to_string(result));
    }

    // Retrieve the Graphics Queue
    vkGetDeviceQueue(
        m_device,                   // Device from where to retrieve the Queue
        queueFamilyIndices.first,   // Queue Family Index
        0,                          // First Queue of the Queue Family
        &m_graphicsQueue            // Retrieval destination
    );

    // Retrieve the Presentation Queue
    vkGetDeviceQueue(
        m_device,                   // Device from where to retrieve the Queue
        queueFamilyIndices.second,  // Queue Family Index
        0,                          // First Queue of the Queue Family
        &m_presentationQueue        // Retrieval destination
    );
}

Device::~Device() {
    if(m_device) {
        vkDestroyDevice(m_device, nullptr);

        m_device = VK_NULL_HANDLE;
        m_graphicsQueue = VK_NULL_HANDLE;
        m_presentationQueue = VK_NULL_HANDLE;
    }
}

Device::operator VkDevice() const noexcept {
    return m_device;
}

Device::operator VkPhysicalDevice() const noexcept {
    return m_physicalDevice;
}

VkQueue Device::getGraphicsQueue() const noexcept {
    return m_graphicsQueue;
}

VkQueue Device::getPresentationQueue() const noexcept {
    return m_presentationQueue;
}

}
)" };

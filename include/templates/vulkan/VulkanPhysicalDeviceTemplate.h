#pragma once

const auto VULKAN_PHYSICAL_DEVICE_H_TEMPLATE { R"(#pragma once

#include "Instance.h"

#include <vulkan/vulkan.h>
#include <vector>

namespace be::vulkan {

class PhysicalDevice {
public:
    static std::vector<PhysicalDevice> enumeratePhysicalDevices(Instance::Ptr instance);

    operator VkPhysicalDevice() const noexcept;

    VkPhysicalDeviceProperties getProperties() const noexcept;
    VkPhysicalDeviceFeatures getFeatures() const noexcept;
    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties() const noexcept;

    bool areExtensionsSupported(const std::vector<const char *> &extensions) const noexcept;
private:
    VkPhysicalDevice m_physicalDevice { VK_NULL_HANDLE };
    VkPhysicalDeviceProperties m_physicalDeviceProperties;
    VkPhysicalDeviceFeatures m_physicalDeviceFeatures;
    std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;
};

}
)" };

const auto VULKAN_PHYSICAL_DEVICE_CPP_TEMPLATE { R"(#include "be/vulkan/PhysicalDevice.h"

namespace be::vulkan {

namespace local_helpers {

std::vector<VkPhysicalDevice> enumeratePhysicalDevices(Instance::Ptr instance) {
    uint32_t physicalDeviceCount { 0 };
    vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, nullptr);

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(*instance, &physicalDeviceCount, physicalDevices.data());

    return physicalDevices;
}

VkPhysicalDeviceProperties getProperties(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);

    return properties;
}

VkPhysicalDeviceFeatures getFeatures(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(physicalDevice, &features);

    return features;
}

std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(VkPhysicalDevice physicalDevice) {
    uint32_t queueFamilyPropertyCount { 0 };
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());

    return queueFamilyProperties;
}

}

std::vector<PhysicalDevice> PhysicalDevice::enumeratePhysicalDevices(Instance::Ptr instance) {
    auto physicalDevices { local_helpers::enumeratePhysicalDevices(instance) };

    std::vector<PhysicalDevice> devices;
    for(auto &physicalDevice : physicalDevices) {
        PhysicalDevice device;

        device.m_physicalDevice = physicalDevice;
        device.m_physicalDeviceProperties = local_helpers::getProperties(physicalDevice);
        device.m_physicalDeviceFeatures = local_helpers::getFeatures(physicalDevice);
        device.m_queueFamilyProperties = local_helpers::getQueueFamilyProperties(physicalDevice);

        devices.push_back(device);
    }
    

    return devices;
}

PhysicalDevice::operator VkPhysicalDevice() const noexcept {
    return m_physicalDevice;
}

VkPhysicalDeviceProperties PhysicalDevice::getProperties() const noexcept {
    return m_physicalDeviceProperties;
}

VkPhysicalDeviceFeatures PhysicalDevice::getFeatures() const noexcept {
    return m_physicalDeviceFeatures;
}

std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties() const noexcept {
    return m_queueFamilyProperties;
}

bool PhysicalDevice::areExtensionsSupported(const std::vector<const char *> &extensions) const noexcept {
    uint32_t extensionCount { 0 };
    vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    for(const auto &extension : extensions) {
        bool found { false };
        for(const auto &availableExtension : availableExtensions) {
            if(strcmp(extension, availableExtension.extensionName) == 0) {
                found = true;
                break;
            }
        }

        if(!found) {
            return false;
        }
    }

    return true;
}

}
)" };

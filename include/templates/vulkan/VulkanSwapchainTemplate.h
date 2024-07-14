#pragma once

const auto VULKAN_SWAPCHAIN_H_TEMPLATE { R"(#pragma once

#include "Device.h"
#include "Surface.h"

#include <SDL3/SDL.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace be::vulkan {

class Swapchain {
public:
    using Ptr = std::shared_ptr<Swapchain>;

    // Constructor
    Swapchain(SDL_Window *pWindow, Device::Ptr device, Surface::Ptr surface);

    // Destructor
    ~Swapchain();

    operator VkSwapchainKHR() const noexcept;

    VkExtent2D getExtent2D() const noexcept;
private:
    // Copy Constructor
    Swapchain(const Swapchain &other) = delete;

    // Move Constructor
    Swapchain(Swapchain &&other) = delete;

    // Copy Assignment
    Swapchain &operator=(const Swapchain &other) = delete;

    // Move Assignment
    Swapchain &operator=(Swapchain &&other) = delete;

    Device::Ptr m_device { nullptr };
    VkSwapchainKHR m_swapchain { VK_NULL_HANDLE };

    std::vector<VkImage> m_swapchainImages;
    std::vector<VkImageView> m_swapchainImageViews;
    
    VkSurfaceFormatKHR m_swapchainFormat;
    VkExtent2D m_swapchainExtent;
};

})" };

const auto VULKAN_SWAPCHAIN_CPP_TEMPLATE { R"(#include "be/vulkan/Swapchain.h"

#include <SDL3/SDL_vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace be::vulkan {

namespace local_helpers {

VkSurfaceFormatKHR getSwapchainSurfaceFormat(Device::Ptr device, Surface::Ptr surface) {
    uint32_t formatCount { 5 };
    std::vector<VkSurfaceFormatKHR> formats(formatCount);

    vkGetPhysicalDeviceSurfaceFormatsKHR(*device, *surface, &formatCount, formats.data());

    return formats[1];
}

VkSurfaceCapabilitiesKHR getSwapchainCapabilities(Device::Ptr device, Surface::Ptr surface) {
    VkSurfaceCapabilitiesKHR capabilities;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*device, *surface, &capabilities);

    return capabilities;
}

VkExtent2D getSwapchainResolutionExtent(SDL_Window *pWindow, VkSurfaceCapabilitiesKHR &capabilities) {
    if(capabilities.currentExtent.width == std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    }

    int width;
    int height;

    SDL_GetWindowSizeInPixels(pWindow, &width, &height);

    VkExtent2D actualExtent = {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height)
    };

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

}

Swapchain::Swapchain(SDL_Window *pWindow, Device::Ptr device, Surface::Ptr surface) : m_device(device) {
    m_swapchainFormat = local_helpers::getSwapchainSurfaceFormat(m_device, surface);
    auto capabilities { local_helpers::getSwapchainCapabilities(m_device, surface) };
    m_swapchainExtent = local_helpers::getSwapchainResolutionExtent(pWindow, capabilities);

    // Trible buffer
    uint32_t imageCount { 3 };

    VkSwapchainCreateInfoKHR createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = m_swapchainFormat.format;
    createInfo.imageColorSpace = m_swapchainFormat.colorSpace;
    createInfo.imageExtent = m_swapchainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    // Both presentation and graphics are in the same queue family
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0;
    createInfo.pQueueFamilyIndices = nullptr;

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;    
    createInfo.clipped = true;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if(VkResult result = vkCreateSwapchainKHR(*m_device, &createInfo, nullptr, &m_swapchain); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create swapchain. Error: " + std::string(string_VkResult(result)));
    }

    m_swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(*m_device, m_swapchain, &imageCount, m_swapchainImages.data());

    for(const auto image : m_swapchainImages) {
        VkImageViewCreateInfo viewCreateInfo{};
        viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewCreateInfo.image = image;
        viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewCreateInfo.format = m_swapchainFormat.format;
        viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewCreateInfo.subresourceRange.baseMipLevel = 0;
        viewCreateInfo.subresourceRange.levelCount = 1;
        viewCreateInfo.subresourceRange.baseArrayLayer = 0;
        viewCreateInfo.subresourceRange.layerCount = 1;

        VkImageView imageView {VK_NULL_HANDLE };
        if(VkResult result = vkCreateImageView(*m_device, &viewCreateInfo, nullptr, &imageView); result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Image View. Error: " + std::string(string_VkResult(result)));
        }

        m_swapchainImageViews.push_back(imageView);
    }
}

Swapchain::~Swapchain() {
    for(const auto view : m_swapchainImageViews) {
        vkDestroyImageView(*m_device, view, nullptr);
    }

    if(m_swapchain) {
        vkDestroySwapchainKHR(*m_device, m_swapchain, nullptr);

        m_swapchain = VK_NULL_HANDLE;
    }
}

Swapchain::operator VkSwapchainKHR() const noexcept {
    return m_swapchain;
}

VkExtent2D Swapchain::getExtent2D() const noexcept {
    return m_swapchainExtent;
}

})" };

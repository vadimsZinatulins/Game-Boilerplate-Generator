#pragma once

const auto VULKAN_SURFACE_H_TEMPLATE { R"(#pragma once

#include "Instance.h"

#include <SDL3/SDL.h>
#include <vulkan/vulkan.h>
#include <memory>

namespace be::vulkan {

class Surface {
public:
    using Ptr = std::shared_ptr<Surface>;

    // Constructor
    Surface(SDL_Window *pWindow, Instance::Ptr instance);

    // Destructor
    ~Surface();

    operator VkSurfaceKHR() const noexcept;
private:
    // Copy Constructor
    Surface(const Surface &other) = delete;

    // Move Constructor
    Surface(Surface &&other) = delete;
    
    // Copy Assignment
    Surface &operator=(const Surface &other) = delete;
    
    // Move Assignment
    Surface &operator=(Surface &&other) = delete;

    Instance::Ptr m_instance;

    VkSurfaceKHR m_surface { VK_NULL_HANDLE };
};

}
)" };

const auto VULKAN_SURFACE_CPP_TEMPLATE { R"(#include "be/vulkan/Surface.h"

#include <SDL3/SDL_vulkan.h>
#include <stdexcept>

namespace be::vulkan {

Surface::Surface(SDL_Window *pWindow, Instance::Ptr instance) : m_instance(instance) {
    if(SDL_Vulkan_CreateSurface(pWindow, *m_instance, nullptr, &m_surface) != 0) {
        throw std::runtime_error("Failed to create Surface! " + std::string(SDL_GetError()));
    }
}

Surface::~Surface() {
    if(m_surface) {
        SDL_Vulkan_DestroySurface(*m_instance, m_surface, nullptr);

        m_surface = nullptr;
    }
}

Surface::operator VkSurfaceKHR() const noexcept {
    return m_surface;
}

}
)" };

#pragma once

const auto VULKAN_QUEUE_CRITERIA_H_TEMPLATE { R"(#pragma once

#include "IDeviceCriteria.h"

#include "../Surface.h"

namespace be::vulkan::device_picker {

class QueueCriteria : public IDeviceCriteria {
public:
    QueueCriteria(Surface::Ptr surface);
    virtual ~QueueCriteria();

    int rateDevice(const PhysicalDevice &device) const noexcept override;
private:
    Surface::Ptr m_surface { nullptr };
};

}
)" };

const auto VULKAN_QUEUE_CRITERIA_CPP_TEMPLATE { R"(#include "be/vulkan/device_picker/QueueCriteria.h"

namespace be::vulkan::device_picker {

QueueCriteria::QueueCriteria(Surface::Ptr surface) : m_surface(surface) {}
QueueCriteria::~QueueCriteria() {}

int QueueCriteria::rateDevice(const PhysicalDevice &device) const noexcept {
    int rating { 0 };

    auto queueFamilies { device.getQueueFamilyProperties() };

    for(int i = 0; i < queueFamilies.size(); i++) {
        int queueRating { 0 };

        VkBool32 presentSupport { false };
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, *m_surface, &presentSupport);

        if(presentSupport) {
            queueRating += 125;
        }

        if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queueRating += 125;
        }

        if(queueRating > rating) {
            rating = queueRating;
        }
    }

    return rating;
}

}
)" };

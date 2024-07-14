#pragma once

const auto VULKAN_BASE_CRITERIA_H_TEMPLATE { R"(#pragma once

#include "IDeviceCriteria.h"

namespace be::vulkan::device_picker {

struct BaseCriteria : public IDeviceCriteria {
    int rateDevice(const PhysicalDevice &device) const noexcept override;
};

}
)" };

const auto VULKAN_BASE_CRITERIA_CPP_TEMPLATE { R"(#include "be/vulkan/device_picker/BaseCriteria.h"

namespace be::vulkan::device_picker {

int BaseCriteria::rateDevice(const PhysicalDevice &device) const noexcept {
    int rating { 0 };

    if(device.getProperties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        rating += 250;
    }

    return rating;
}

}
)" };

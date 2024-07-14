#pragma once

const auto VULKAN_DEVICE_PICKER_H_TEMPLATE { R"(#pragma once

#include "../PhysicalDevice.h"
#include "IDeviceCriteria.h"

#include <vector>
#include <optional>

namespace be::vulkan::device_picker {

class DevicePicker {
public:
    DevicePicker() = default;
    virtual ~DevicePicker() = default;

    DevicePicker &addCriteria(IDeviceCriteria::Ptr criteria) noexcept;

    std::optional<PhysicalDevice> pickDevice(const std::vector<PhysicalDevice> &devices) const noexcept;
private:
    struct PhysicalDeviceRating {
        PhysicalDevice device;
        int rating;
    };

    std::vector<IDeviceCriteria::Ptr> m_criterias;
};

}
)" };

const auto VULKAN_DEVICE_PICKER_CPP_TEMPLATE { R"(#include "be/vulkan/device_picker/DevicePicker.h"

#include <algorithm>

namespace be::vulkan::device_picker {

DevicePicker &DevicePicker::addCriteria(IDeviceCriteria::Ptr criteria) noexcept {
    m_criterias.push_back(criteria);

    return *this;
}

std::optional<PhysicalDevice> DevicePicker::pickDevice(const std::vector<PhysicalDevice> &devices) const noexcept {
    // List of all physical devices available with score higher than 0
    std::vector<PhysicalDeviceRating> ratings;
    // Rate each device based on the criteria
    for(auto &device : devices) {
        // Rate the device based on the criteria
        int rating { 0 };
        for(auto &criteria : m_criterias) {
            rating += criteria->rateDevice(device);
        }

        // Add device to the list if it has a score higher than 0
        if(rating > 0) {
            ratings.push_back({ device, rating });
        }
    }

    // Pick the device with the highest score
    auto bestRating { std::max_element(ratings.begin(), ratings.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.rating < rhs.rating;
    }) };

    // If no suitable device was found, return a null optional
    if(bestRating == ratings.end()) {
        return std::nullopt;
    }

    // Return the best rated device
    return bestRating->device;
}

}
)" };

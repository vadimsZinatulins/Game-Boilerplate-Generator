#pragma once

const auto VULKAN_IDEVICE_CRITERIA_H_TEMPLATE { R"(#pragma once

#include "../PhysicalDevice.h"

#include <memory>

namespace be::vulkan::device_picker {

struct IDeviceCriteria {
    using Ptr = std::shared_ptr<IDeviceCriteria>;

    IDeviceCriteria() = default;
    virtual ~IDeviceCriteria() = default;

    virtual int rateDevice(const PhysicalDevice &device) const noexcept = 0;
};

}
)" };

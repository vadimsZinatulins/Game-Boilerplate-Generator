#pragma once

const auto VULKAN_EXTENSION_CRITERIA_H_TEMPLATE { R"(#pragma once

#include "IDeviceCriteria.h"

#include <vector>

namespace be::vulkan::device_picker {

class ExtensionCriteria : public IDeviceCriteria {
public:
    ExtensionCriteria(const std::vector<const char *> &requiredExtensions) noexcept;
    virtual ~ExtensionCriteria();

    int rateDevice(const PhysicalDevice &device) const noexcept override;
private:
    std::vector<const char *> m_requiredExtensions;
};

}
)" };

const auto VULKAN_EXTENSION_CRITERIA_CPP_TEMPLATE { R"(#include "be/vulkan/device_picker/ExtensionCriteria.h"

#include <vector>

namespace be::vulkan::device_picker {

ExtensionCriteria::ExtensionCriteria(const std::vector<const char *> &requiredExtensions) noexcept : m_requiredExtensions(requiredExtensions) {}
ExtensionCriteria::~ExtensionCriteria() {}

int ExtensionCriteria::rateDevice(const PhysicalDevice &device) const noexcept {
    int rating { 0 };

    if(device.areExtensionsSupported(m_requiredExtensions)) {
        rating += 500;
    } else {
        return -10000;
    }

    return rating;
}

}
)" };

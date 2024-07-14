#pragma once

const auto VULKAN_SHADER_MODULE_H_TEMPLATE { R"(#pragma once

#include "Device.h"

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <string>

namespace be::vulkan {

class ShaderModule {
public:
    using Ptr = std::shared_ptr<ShaderModule>;

    // Constructor
    ShaderModule(const std::string &filePath, Device::Ptr device);

    // Destructor
    ~ShaderModule();

    operator VkShaderModule() const noexcept;
private:
    // Copy Constructor
    ShaderModule(const ShaderModule &other) = delete;

    // Move Constructor
    ShaderModule(ShaderModule &&other) = delete;

    // Copy Assignment
    ShaderModule operator=(const ShaderModule &other) = delete;

    // Move Assignment
    ShaderModule operator=(ShaderModule &&other) = delete;

    Device::Ptr m_device { nullptr };
    VkShaderModule m_module { VK_NULL_HANDLE };
};

}
)" };

const auto VULKAN_SHADER_MODULE_CPP_TEMPLATE { R"(#include "be/vulkan/ShaderModule.h"

#include <vulkan/vk_enum_string_helper.h>
#include <fstream>

namespace be::vulkan {

namespace local_helpers {

std::vector<char> read(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);

    if(!file.is_open()) {
        throw std::runtime_error("Failed to open file at " + filePath);
    }

    std::size_t fileSize = (std::size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

}

ShaderModule::ShaderModule(const std::string &filePath, Device::Ptr device) : m_device(device) {
    auto shaderCode { local_helpers::read(filePath) };

    VkShaderModuleCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

    if(VkResult result = vkCreateShaderModule(*m_device, &createInfo, nullptr, &m_module); result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module. Error: "  + std::string(string_VkResult(result)));
    }
}

ShaderModule::~ShaderModule() {
    if(m_module) {
        vkDestroyShaderModule(*m_device, m_module, nullptr);

        m_module = VK_NULL_HANDLE;
    }
}


ShaderModule::operator VkShaderModule() const noexcept {
    return m_module;
}

}
)" };

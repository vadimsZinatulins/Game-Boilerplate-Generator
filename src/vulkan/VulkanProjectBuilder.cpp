#include "vulkan/VulkanProjectBuilder.h"
#include "Logger.h"
#include "utils/replaceAll.h"

// Vulkan templates
#include "templates/vulkan/VulkanInstanceTemplate.h"
#include "templates/vulkan/VulkanDebugMessengerTemplate.h"
#include "templates/vulkan/VulkanSurfaceTemplate.h"
#include "templates/vulkan/VulkanPhysicalDeviceTemplate.h"
#include "templates/vulkan/VulkanDeviceTemplate.h"
#include "templates/vulkan/VulkanSwapchainTemplate.h"
#include "templates/vulkan/VulkanIDeviceCriteriaTemplate.h"
#include "templates/vulkan/VulkanBaseCriteriaTemplate.h"
#include "templates/vulkan/VulkanExtensionCriteria.h"
#include "templates/vulkan/VulkanQueueCriteriaTemplate.h"
#include "templates/vulkan/VulkanDevicePickerTemplate.h"
#include "templates/vulkan/VulkanShaderModuleTemplate.h"
#include "templates/vulkan/VulkanPipelineTemplate.h"
#include "templates/vulkan/VulkanShadersTemplate.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace gbg {

void buildVulkanProject(std::shared_ptr<stm::Task<void>> generateWorkspaceTask, const std::string &projectName) {
	auto generateVulkanInstance { stm::make_task([projectName] {
        Log() << "Generating Instance files\n";
        {
            std::ofstream instanceCppFile("src/be/vulkan/Instance.cpp");
            instanceCppFile << replaceAll(VULKAN_INSTANCE_CPP_TEMPLATE, { { "{PROJECT_NAME}", projectName } });
            instanceCppFile.close();
        }
        
        {
            std::ofstream instanceHFile("include/be/vulkan/Instance.h");
            instanceHFile << VULKAN_INSTANCE_H_TEMPLATE;
            instanceHFile.close();
        }
	}, generateWorkspaceTask) };

	auto generateVulkanDebug { stm::make_task([] {
        Log() << "Generating DebugMessenger files\n";
        {
            std::ofstream debugCppFile("src/be/vulkan/DebugMessenger.cpp");
            debugCppFile << VULKAN_DEBUG_CPP_TEMPLATE;
            debugCppFile.close();
        }
        
        {
            std::ofstream debugHFile("include/be/vulkan/DebugMessenger.h");
            debugHFile << VULKAN_DEBUG_H_TEMPLATE;
            debugHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanSurface { stm::make_task([] {
        Log() << "Generating Surface files\n";
        {
            std::ofstream surfaceCppFile("src/be/vulkan/Surface.cpp");
            surfaceCppFile << VULKAN_SURFACE_CPP_TEMPLATE;
            surfaceCppFile.close();
        }
        
        {
            std::ofstream surfaceHFile("include/be/vulkan/Surface.h");
            surfaceHFile << VULKAN_SURFACE_H_TEMPLATE;
            surfaceHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanPhysicalDevice { stm::make_task([] {
        Log() << "Generating PhysicalDevice files\n";
        {
            std::ofstream physicalDeviceCppFile("src/be/vulkan/PhysicalDevice.cpp");
            physicalDeviceCppFile << VULKAN_PHYSICAL_DEVICE_CPP_TEMPLATE;
            physicalDeviceCppFile.close();
        }
        
        {
            std::ofstream physicalDeviceHFile("include/be/vulkan/PhysicalDevice.h");
            physicalDeviceHFile << VULKAN_PHYSICAL_DEVICE_H_TEMPLATE;
            physicalDeviceHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanDevice { stm::make_task([] {
        Log() << "Generating Device files\n";
        {
            std::ofstream deviceCppFile("src/be/vulkan/Device.cpp");
            deviceCppFile << VULKAN_DEVICE_CPP_TEMPLATE;
            deviceCppFile.close();
        }
        
        {
            std::ofstream deviceHFile("include/be/vulkan/Device.h");
            deviceHFile << VULKAN_DEVICE_H_TEMPLATE;
            deviceHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanSwapchain { stm::make_task([] {
        Log() << "Generating Swapchain files\n";
        {
            std::ofstream swapchainCppFile("src/be/vulkan/Swapchain.cpp");
            swapchainCppFile << VULKAN_SWAPCHAIN_CPP_TEMPLATE;
            swapchainCppFile.close();
        }
        
        {
            std::ofstream swapchainHFile("include/be/vulkan/Swapchain.h");
            swapchainHFile << VULKAN_SWAPCHAIN_H_TEMPLATE;
            swapchainHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanIDeviceCriteria { stm::make_task([] {
        Log() << "Generating IDeviceCriteria file\n";
        {
            std::ofstream iDeviceCriteriaHFile("include/be/vulkan/device_picker/IDeviceCriteria.h");
            iDeviceCriteriaHFile << VULKAN_IDEVICE_CRITERIA_H_TEMPLATE;
            iDeviceCriteriaHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanBaseCriteria { stm::make_task([] {
        Log() << "Generating BaseCriteria files\n";
        {
            std::ofstream baseCriteriaCppFile("src/be/vulkan/device_picker/BaseCriteria.cpp");
            baseCriteriaCppFile << VULKAN_BASE_CRITERIA_CPP_TEMPLATE;
            baseCriteriaCppFile.close();
        }
        
        {
            std::ofstream baseCriteriaHFile("include/be/vulkan/device_picker/BaseCriteria.h");
            baseCriteriaHFile << VULKAN_BASE_CRITERIA_H_TEMPLATE;
            baseCriteriaHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanExtensionCriteria { stm::make_task([] {
        Log() << "Generating ExtensionCriteria files\n";
        {
            std::ofstream extensionCriteriaCppFile("src/be/vulkan/device_picker/ExtensionCriteria.cpp");
            extensionCriteriaCppFile << VULKAN_EXTENSION_CRITERIA_CPP_TEMPLATE;
            extensionCriteriaCppFile.close();
        }
        
        {
            std::ofstream extensionCriteriaHFile("include/be/vulkan/device_picker/ExtensionCriteria.h");
            extensionCriteriaHFile << VULKAN_EXTENSION_CRITERIA_H_TEMPLATE;
            extensionCriteriaHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanQueueCriteria { stm::make_task([] {
        Log() << "Generating QueueCriteria files\n";
        {
            std::ofstream queueCriteriaCppFile("src/be/vulkan/device_picker/QueueCriteria.cpp");
            queueCriteriaCppFile << VULKAN_QUEUE_CRITERIA_CPP_TEMPLATE;
            queueCriteriaCppFile.close();
        }
        
        {
            std::ofstream queueCriteriaHFile("include/be/vulkan/device_picker/QueueCriteria.h");
            queueCriteriaHFile << VULKAN_QUEUE_CRITERIA_H_TEMPLATE;
            queueCriteriaHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanDevicePicker { stm::make_task([] {
        Log() << "Generating DevicePicker files\n";
        {
            std::ofstream devicePickerCppFile("src/be/vulkan/device_picker/DevicePicker.cpp");
            devicePickerCppFile << VULKAN_DEVICE_PICKER_CPP_TEMPLATE;
            devicePickerCppFile.close();
        }
        
        {
            std::ofstream devicePickerHFile("include/be/vulkan/device_picker/DevicePicker.h");
            devicePickerHFile << VULKAN_DEVICE_PICKER_H_TEMPLATE;
            devicePickerHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanShaderModule { stm::make_task([] {
        Log() << "Generating ShaderModule files\n";
        {
            std::ofstream shaderModuleCppFile("src/be/vulkan/ShaderModule.cpp");
            shaderModuleCppFile << VULKAN_SHADER_MODULE_CPP_TEMPLATE;
            shaderModuleCppFile.close();
        }
        
        {
            std::ofstream shaderModuleHFile("include/be/vulkan/ShaderModule.h");
            shaderModuleHFile << VULKAN_SHADER_MODULE_H_TEMPLATE;
            shaderModuleHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanPipeline { stm::make_task([] {
        Log() << "Generating Pipeline files\n";
        {
            std::ofstream pipelineCppFile("src/be/vulkan/Pipeline.cpp");
            pipelineCppFile << VULKAN_PIPELINE_CPP_TEMPLATE;
            pipelineCppFile.close();
        }
        
        {
            std::ofstream pipelineHFile("include/be/vulkan/Pipeline.h");
            pipelineHFile << VULKAN_PIPELINE_H_TEMPLATE;
            pipelineHFile.close();
        }
	}, generateWorkspaceTask) };
	
	auto generateVulkanShaders { stm::make_task([] {
        Log() << "Generating Shader files\n";
        {
            std::ofstream vertexShaderFile("shaders/vertex.vert");
            vertexShaderFile << VULKAN_SHADER_VERT_TEMPLATE;
            vertexShaderFile.close();
        }
        
        {
            std::ofstream fragmentShaderFile("shaders/fragment.frag");
            fragmentShaderFile << VULKAN_SHADER_FRAG_TEMPLATE;
            fragmentShaderFile.close();
        }
	}, generateWorkspaceTask) };

	generateVulkanInstance->result();
	generateVulkanDebug->result();
	generateVulkanSurface->result();
	generateVulkanPhysicalDevice->result();
    generateVulkanDevice->result();
    generateVulkanSwapchain->result();
	generateVulkanIDeviceCriteria->result();
	generateVulkanBaseCriteria->result();
	generateVulkanExtensionCriteria->result();
	generateVulkanQueueCriteria->result();
	generateVulkanDevicePicker->result();
	generateVulkanShaderModule->result();
    generateVulkanPipeline->result();
}

}

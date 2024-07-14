#pragma once

#include <memory>
#include <string>
#include <SimpleTaskManager/make_task.h>

namespace gbg {

void buildVulkanProject(std::shared_ptr<stm::Task<void>> generateWorkspaceTask, const std::string &projectName);

}
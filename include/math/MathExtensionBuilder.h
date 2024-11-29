#pragma once

namespace gbg {

void buildVulkanProject(std::shared_ptr<stm::Task<void>> generateWorkspaceTask, const std::string &projectName);

}
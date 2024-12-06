#pragma once

#include <memory>
#include <SimpleTaskManager/Task.h>
#include <string>

namespace gbg {

void buildMathExtension(std::shared_ptr<stm::Task<void>> generateWorkspaceTask, const std::string &projectName);

}
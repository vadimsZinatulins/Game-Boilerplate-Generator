#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "utils/replaceAll.h"
#include "generators/Generator.h"
#include "templates/ProjectClassTemplate.h"
#include "Logger.h"

namespace gbg {

class ProjectNameFileGenerator : public Generator {
public:
    ProjectNameFileGenerator(std::string projectName) : m_projectName(projectName) {}

    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating " + m_projectName + " Class", LogType::Verbose);

            std::ofstream projectClassHFile("include/" + m_projectName + ".h");
            projectClassHFile << replaceAll(PROJECTCLASS_H_TEMPLATE, { { "{NAME}", m_projectName } });
            projectClassHFile.close();

            std::ofstream projectClassCppFile("src/" + m_projectName + ".cpp");
            projectClassCppFile << replaceAll(PROJECTCLASS_CPP_TEMPLATE, { { "{NAME}", m_projectName } });
            projectClassCppFile.close();
        }, dependency);
    }

private:
    std::string m_projectName;
};

}

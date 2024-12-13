#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "utils/replaceAll.h"
#include "generators/Generator.h"
#include "templates/MainTemplate.h"
#include "Logger.h"

namespace gbg {

class MainFileGenerator : public Generator {
public:
    MainFileGenerator(std::string projectName) : m_projectName(projectName) {}

    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating main.cpp file", LogType::Verbose);

            std::ofstream mainFile("src/main.cpp");
            mainFile << replaceAll(MAIN_CPP_TEMPLATE, { { "{NAME}", m_projectName } });
            mainFile.close();
        }, dependency);
    }

private:
    std::string m_projectName;
};

}

#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "utils/replaceAll.h"
#include "generators/Generator.h"
#include "templates/ConfigTemplate.h"
#include "Logger.h"

namespace gbg {

class ConfigFileGenerator : public Generator {
public:
    ConfigFileGenerator(std::string projectName)
        : m_projectName(projectName) { }
    ~ConfigFileGenerator() override = default;

    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating config.h.in file", LogType::Verbose);

            ReplaceContent rc = { { "{NAME}", m_projectName } };

            std::ofstream configHInFile("config/config.h.in");
            configHInFile << replaceAll(CONFIG_H_IN_TEMPLATE, rc);
            configHInFile.close();
        }, dependency);
    }
private:
    std::string m_projectName;
};

}
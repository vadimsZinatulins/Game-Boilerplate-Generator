#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/MouseManagerTemplate.h"
#include "Logger.h"

namespace gbg {

struct MouseManagerGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating MouseManager Class", LogType::Verbose);

            std::ofstream mouseManagerHFile("include/be/MouseManager.h");
            mouseManagerHFile << MOUSEMANAGER_H_TEMPLATE;
            mouseManagerHFile.close();

            std::ofstream mouseManagerCppFile("src/be/MouseManager.cpp");
            mouseManagerCppFile << MOUSEMANAGER_CPP_TEMPLATE;
            mouseManagerCppFile.close();
        }, dependency);
    }
};

}

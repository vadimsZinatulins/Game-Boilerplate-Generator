#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/SceneManagerTemplate.h"
#include "Logger.h"

namespace gbg {

struct SceneManagerGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating SceneManager Class", LogType::Verbose);

            std::ofstream sceneManagerHFile("include/be/SceneManager.h");
            sceneManagerHFile << SCENEMANAGER_H_TEMPLATE;
            sceneManagerHFile.close();

            std::ofstream sceneManagerCppFile("src/be/SceneManager.cpp");
            sceneManagerCppFile << SCENEMANAGER_CPP_TEMPLATE;
            sceneManagerCppFile.close();
        }, dependency);
    }
};

}


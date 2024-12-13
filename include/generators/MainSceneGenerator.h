#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/MainSceneTemplate.h"
#include "Logger.h"

namespace gbg {

struct MainSceneGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating MainScene Class", LogType::Verbose);

            std::ofstream mainSceneHFile("include/MainScene.h");
            mainSceneHFile << MAINSCENE_H_TEMPLATE;
            mainSceneHFile.close();

            std::ofstream mainSceneCppFile("src/MainScene.cpp");
            mainSceneCppFile << MAINSCENE_CPP_TEMPLATE;
            mainSceneCppFile.close();
        }, dependency);
    }
};

}

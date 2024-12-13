#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/ISceneTemplate.h"
#include "Logger.h"

namespace gbg {

struct ISceneGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating IScene Class", LogType::Verbose);

            std::ofstream isceneHFile("include/be/IScene.h");
            isceneHFile << ISCENE_H_TEMPLATE;
            isceneHFile.close();
        }, dependency);
    }
};

}

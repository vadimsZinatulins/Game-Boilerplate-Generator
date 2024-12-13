#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/GameTemplate.h"
#include "Logger.h"

namespace gbg {

struct GameGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating Game Class", LogType::Verbose);

            std::ofstream gameHFile("include/be/Game.h");
            gameHFile << GAME_H_TEMPLATE;
            gameHFile.close();
        }, dependency);
    }
};

}


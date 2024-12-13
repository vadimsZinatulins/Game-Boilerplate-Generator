#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/RandomTemplate.h"
#include "Logger.h"

namespace gbg {

struct RandomGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating Random Class", LogType::Verbose);

            std::ofstream randomHFile("include/be/Random.h");
            randomHFile << RANDOM_H_TEMPLATE;
            randomHFile.close();

            std::ofstream randomCppFile("src/be/Random.cpp");
            randomCppFile << RANDOM_CPP_TEMPLATE;
            randomCppFile.close();

        }, dependency);
    }
};

}

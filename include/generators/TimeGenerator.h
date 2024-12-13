#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/TimeTemplate.h"
#include "Logger.h"

namespace gbg {

struct TimeGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating Time Class", LogType::Verbose);

            std::ofstream timerHFile("include/be/Time.h");
            timerHFile << TIMER_H_TEMPLATE;
            timerHFile.close();

            std::ofstream timerCppFile("src/be/Time.cpp");
            timerCppFile << TIMER_CPP_TEMPLATE;
            timerCppFile.close();
        }, dependency);
    }
};

}

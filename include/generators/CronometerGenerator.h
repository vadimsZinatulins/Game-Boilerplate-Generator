#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/CronometerTemplate.h"
#include "Logger.h"

namespace gbg {

struct CronometerGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating Cronometer Class", LogType::Verbose);

            std::ofstream cronometerHFile("include/be/Cronometer.h");
            cronometerHFile << CRONOMETER_H_TEMPLATE;
            cronometerHFile.close();

            std::ofstream cronometerCppFile("src/be/Cronometer.cpp");
            cronometerCppFile << CRONOMETER_CPP_TEMPLATE;
            cronometerCppFile.close();
        }, dependency);
    }
};

}

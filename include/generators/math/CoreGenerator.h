#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/core.h"

namespace gbg {

struct CoreGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Core Math file", LogType::Verbose);

            std::ofstream coreHFile("include/be/math/core.h");
            coreHFile << CORE_H_IN_TEMPLATE;
            coreHFile.close();
        }, dependency);
    }
};

}

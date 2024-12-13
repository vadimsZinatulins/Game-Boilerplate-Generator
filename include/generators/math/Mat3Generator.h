#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/Mat3.h"

namespace gbg {

struct Mat3Generator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Mat3 files", LogType::Verbose);

            std::ofstream mat3CppFile("src/be/math/Mat3.cpp");
            mat3CppFile << MAT3_CPP_TEMPLATE;
            mat3CppFile.close();

            std::ofstream mat3HFile("include/be/math/Mat3.h");
            mat3HFile << MAT3_H_TEMPLATE;
            mat3HFile.close();
        }, dependency);
    }
};

}

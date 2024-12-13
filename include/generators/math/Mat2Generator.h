#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/Mat2.h"

namespace gbg {

struct Mat2Generator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Mat2 files", LogType::Verbose);

            std::ofstream mat2CppFile("src/be/math/Mat2.cpp");
            mat2CppFile << MAT2_CPP_TEMPLATE;
            mat2CppFile.close();

            std::ofstream mat2HFile("include/be/math/Mat2.h");
            mat2HFile << MAT2_H_TEMPLATE;
            mat2HFile.close();
        }, dependency);
    }
};

}

#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/Vec4.h"

namespace gbg {

struct Vec4Generator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Vec4 files", LogType::Verbose);

            std::ofstream vec4CppFile("src/be/math/Vec4.cpp");
            vec4CppFile << VEC4_CPP_TEMPLATE;
            vec4CppFile.close();

            std::ofstream vec4HFile("include/be/math/Vec4.h");
            vec4HFile << VEC4_H_TEMPLATE;
            vec4HFile.close();
        }, dependency);
    }
};

}

#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/Vec2.h"

namespace gbg {

struct Vec2Generator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Vec2 files", LogType::Verbose);

            std::ofstream vec2CppFile("src/be/math/Vec2.cpp");
            vec2CppFile << VEC2_CPP_TEMPLATE;
            vec2CppFile.close();

            std::ofstream vec2HFile("include/be/math/Vec2.h");
            vec2HFile << VEC2_H_TEMPLATE;
            vec2HFile.close();
        }, dependency);
    }
};

}
#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "Logger.h"
#include "templates/math/Vec3.h"

namespace gbg {

struct Vec3Generator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([] {
            Log().log("Generating Vec3 files", LogType::Verbose);

            std::ofstream vec3CppFile("src/be/math/Vec3.cpp");
            vec3CppFile << VEC3_CPP_TEMPLATE;
            vec3CppFile.close();

            std::ofstream vec3HFile("include/be/math/Vec3.h");
            vec3HFile << VEC3_H_TEMPLATE;
            vec3HFile.close();
        }, dependency);
    }
};

}

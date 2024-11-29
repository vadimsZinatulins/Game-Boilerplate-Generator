#include "math/MathExtensionBuilder.h"
#include "Logger.h"

#include "templates/math/core.h"
#include "templates/math/Vec2.h"
#include "templates/math/Vec3.h"
#include "templates/math/Vec4.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace gbg {

void buildVulkanProject(std::shared_ptr<stm::Task<void>> generateWorkspaceTask, const std::string &projectName) {
    auto generateCoreStruct { stm::make_task([] {
        Log() << "Generating Core Math file\n";

        std::ofstream coreHFile("include/be/math/core.h");
        coreHFile << CORE_H_TEMPLATE;
        coreHFile.close();
    }, generateWorkspaceTask) };

    auto generateVec2Struct { stm::make_task([] {
        Log() << "Generating Vec2 files\n";

        {
            std::ofstream vec2CppFile("src/be/math/Vec2.cpp");
            vec2CppFile << VEC2_CPP_TEMPLATE;
            vec2CppFile.close();
        }
        
        {
            std::ofstream vec2HFile("include/be/math/Vec2.h");
            vec2HFile << VEC2_H_TEMPLATE;
            vec2HFile.close();
        }
    }, generateWorkspaceTask) };

    auto generateVec3Struct { stm::make_task([] {
        Log() << "Generating Vec3 files\n";

        {
            std::ofstream vec3CppFile("src/be/math/Vec3.cpp");
            vec3CppFile << VEC3_CPP_TEMPLATE;
            vec3CppFile.close();
        }
        
        {
            std::ofstream vec3HFile("include/be/math/Vec3.h");
            vec3HFile << VEC3_H_TEMPLATE;
            vec3HFile.close();
        }
    }, generateWorkspaceTask) };

    auto generateVec4Struct { stm::make_task([] {
        Log() << "Generating Vec4 files\n";

        {
            std::ofstream vec4CppFile("src/be/math/Vec4.cpp");
            vec4CppFile << VEC4_CPP_TEMPLATE;
            vec4CppFile.close();
        }
        
        {
            std::ofstream vec4HFile("include/be/math/Vec4.h");
            vec4HFile << VEC4_H_TEMPLATE;
            vec4HFile.close();
        }
    }, generateWorkspaceTask) };

    generateCoreStruct->result();
    generateVec2Struct->result();
    generateVec3Struct->result();
    generateVec4Struct->result();
}

}
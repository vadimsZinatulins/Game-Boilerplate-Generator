#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>

#include "generators/Generator.h"
#include "templates/KeyManagerTemplate.h"
#include "Logger.h"

namespace gbg {

struct KeyManagerGenerator : public Generator {
    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating KeyManager Class", LogType::Verbose);
            
            // Generate the header file
            std::ofstream hFile("include/be/KeyManager.h");
            hFile << KEYMANAGER_H_TEMPLATE;
            hFile.close();
            
            // Generate the source file
            std::ofstream cppFile("src/be/KeyManager.cpp");
            cppFile << KEYMANAGER_CPP_TEMPLATE;
            cppFile.close();
        }, dependency);
    }
};

}

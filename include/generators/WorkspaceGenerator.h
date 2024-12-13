#pragma once

#include <SimpleTaskManager/make_task.h>
#include <filesystem>
#include <string>

#include "generators/Generator.h"
#include "Logger.h"

namespace gbg {

class WorkspaceGenerator : public Generator {
public:
    WorkspaceGenerator(std::string projectName, bool withMathExtra)
        : m_projectName(projectName), m_withMathExtra(withMathExtra) { }
    ~WorkspaceGenerator() override = default;

    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            Log().log("Generating workspace", LogType::Verbose);

            // Create a directory with projects name
            std::filesystem::create_directory(m_projectName);

            // Go to the created directory
            std::filesystem::current_path(std::filesystem::current_path().string() + "/" + m_projectName);

            std::vector<const char*> directories { "src", "src/be", "config", "include", "include/be" };
            if(m_withMathExtra) {
                directories.push_back("include/be/math");
                directories.push_back("src/be/math");
            }

            // Create the following directories
            for(const auto &dir : directories) {
                std::filesystem::create_directory(dir);
            }
        });
    }
private:
    std::string m_projectName;
    bool m_withMathExtra;
};

}

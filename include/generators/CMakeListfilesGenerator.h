#pragma once

#include <SimpleTaskManager/make_task.h>
#include <fstream>
#include <sstream>
#include <vector>

#include "generators/Generator.h"
#include "templates/ListFilesTemplate.h"
#include "Logger.h"
#include "utils/replaceAll.h"

namespace gbg {

class CMakeListfilesGenerator : public Generator {
public:
    CMakeListfilesGenerator(std::string projectName, bool withSdlImageExtra, bool withMathExtra)
        : m_projectName(projectName), m_withSdlImageExtra(withSdlImageExtra), m_withMathExtra(withMathExtra) { }
    ~CMakeListfilesGenerator() override = default;

    std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) override {
        return stm::make_task([this] {
            {
                Log().log("Generating CMakeLists.txt", LogType::Verbose);

                std::ofstream rootListfile("CMakeLists.txt");
                
                ReplaceContent rc = {
                    { "{SDL3_IMAGE_FETCH_CONTENT}", m_withSdlImageExtra ? ROOT_LISTFILE_SDL3_IMAGE_FETCH_CONTENT_TEMPLATE : "" },
                    { "{NAME}", m_projectName }
                };

                rootListfile << replaceAll(ROOT_LISTFILE_TEMPLATE, rc);
                rootListfile.close();
            }

            {
                Log().log("Generating src/CMakeLists.txt", LogType::Verbose);

                std::ofstream srcListfile("src/CMakeLists.txt");
                
                ReplaceContent rc = {
                    { "{NAME}", m_projectName },
                    { "{MATH_FILES}", m_withMathExtra ? 
                        "\n\n# Math extension files\n"
                        "\t\tbe/math/Vec2.cpp\n"
                        "\t\tbe/math/Vec3.cpp\n"
                        "\t\tbe/math/Vec4.cpp\n" : "" 
                    },
                    { "{LIBRARIES}", 
                        "\t\tSDL3::SDL3-static\n"
                        + std::string(m_withSdlImageExtra ? "\t\tSDL3_image::SDL3_image\n" : "")
                    }
                };

                srcListfile << replaceAll(SRC_LISTFILE_TEMPLATE, rc);
                srcListfile.close();
            }
        }, dependency);
    }
private:
    std::string m_projectName;
    bool m_withMathExtra;
    bool m_withSdlImageExtra;
};

}

#include "cmakelists.h"

#include <fstream>
#include <vector>
#include <sstream>

std::string addExecutable(std::vector<std::string> cppFiles)
{
	std::stringstream ss;

	ss << "add_executable(\n";
	ss << "\t${PROJECT_NAME}\n";
	for(const auto &cppFile : cppFiles) ss << "\t${PROJECT_SOURCE_DIR}/src/" << cppFile << "\n";
	ss << ")\n";

	return ss.str();
}

void generateCMakeLists(const std::string &projectName)
{
	std::ofstream file("CMakeLists.txt");

	file << "cmake_minimum_required(VERSION 3.10)\n\n"; 
	file << "project(" << projectName << " VERSION 1.0)\n\n"; 
	file << "set(CMAKE_CXX_STANDARD 17)\n"; 
	file << "set(CMAKE_CXX_STANDARD_REQUIRED True)\n"; 
	file << "set(CMAKE_EXPORT_COMPILE_COMMANDS On)\n\n"; 
	file << "find_package(SDL2 REQUIRED)\n\n"; 
	file << "configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)\n\n"; 
	// file << "add_executable(\n\t${PROJECT_NAME} \n\t${PROJECT_SOURCE_DIR}/src/main.cpp\n\t${PROJECT_SOURCE_DIR}/src/KeyManager.cpp\n)\n\n"; 
	file << addExecutable({ "main.cpp", "Game.cpp", "KeyManager.cpp", projectName + ".cpp" });
	file << "target_include_directories(\n\t${PROJECT_NAME}\n\tPUBLIC ${PROJECT_SOURCE_DIR}/include\n\tPUBLIC ${SDL2_INCLUDE_DIRS}\n)\n\n"; 
	file << "target_link_libraries(\n\t${PROJECT_NAME}\n\tPUBLIC ${SDL2_LIBRARIES}\n)\n\n"; 
	file << "set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)\n"; 

	file.close();
}


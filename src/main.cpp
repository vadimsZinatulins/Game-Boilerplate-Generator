#include "config.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

void generateWorkspace(const std::string &projectName)
{
	std::filesystem::create_directory(projectName);
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);
	for(const auto &dir : { "bin", "build", "config", "include", "src" }) std::filesystem::create_directory(dir);
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
	file << "add_executable(\n\t${PROJECT_NAME} \n\t${PROJECT_SOURCE_DIR}/src/main.cpp\n)\n\n"; 
	file << "target_include_directories(\n\t${PROJECT_NAME}\n\tPUBLIC ${PROJECT_SOURCE_DIR}/include\n\tPUBLIC ${SDL2_INCLUDE_DIRS}\n)\n\n"; 
	file << "target_link_libraries(\n\t${PROJECT_NAME}\n\tPUBLIC ${SDL2_LIBRARIES}\n)\n\n"; 
	file << "set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)\n"; 

	file.close();
}

int main(int argc, char *argv[])
{
	std::cout << "Running gbgen version: " << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
	if(argc != 2)
	{
		std::cout << "Wrong argument count" << std::endl;
		std::cout << "Usage: gbgen [PROJECT_NAME]" << std::endl;

		return 1;
	}

	std::string projectName(argv[1]);

	generateWorkspace(projectName);
	generateCMakeLists(projectName);

	return 0;
}

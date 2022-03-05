#include "cmakelists.h"
#include "utils.h"

#include <sstream>

std::string addExecutable(std::vector<std::string> cppFiles)
{
	std::stringstream ss;

	ss << "add_executable(\n";
	ss << "\t${PROJECT_NAME}\n";
	for(const auto &cppFile : cppFiles) ss << "\t${PROJECT_SOURCE_DIR}/src/" << cppFile << ".cpp\n";
	ss << ")\n";

	return ss.str();
}

void generateCMakeLists(const std::string &projectName, std::vector<std::string> cppFiles)
{
	mkfile("CMakeLists.txt", {
			"# Minimum cmake version required to run this text file",
			"cmake_minimum_required(VERSION 3.10)",
			"",
			"# Project name",
			"project(" + projectName + ")",
			"# C++ standard",
			"set(CMAKE_CXX_STANDARD 17)",
			"# Force the C++ standard",
			"set(CMAKE_CXX_STANDARD_REQUIRED True)",
			"# Generate compile commands (this for vim)",
			"set(CMAKE_EXPORT_COMPILE_COMMANDS On)",
			"",
			"# Find the SDL2 library",
			"find_package(SDL2 REQUIRED)",
			"",
			"# Project configuration file",
			"configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)",
			"",
			"# Create the executable from following cpp files",
			addExecutable(std::move(cppFiles)),
			"# Include these directories in the project",
			"target_include_directories(",
			"	${PROJECT_NAME}",
			"	PUBLIC ${PROJECT_SOURCE_DIR}/include",
			"	PUBLIC ${SDL2_INCLUDE_DIRS}",
			")",
			"# Libraries to link to the project",
			"target_link_libraries(",
			"	${PROJECT_NAME}",
			"	PUBLIC ${SDL2_LIBRARIES}",
			")",
			"",
			"# Set output directory",
			"set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)"
	});
}


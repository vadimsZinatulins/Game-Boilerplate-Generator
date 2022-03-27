#include "CMakeFile.h"
#include "utils/Instruction.h"
#include "utils/File.h"
#include <sstream>

void CMakeFile::setVersion(std::size_t major, std::size_t minor)
{
	m_majorVersion = major;
	m_minorVersion = minor;
}

void CMakeFile::addFileToCompile(std::string newFile)
{
	m_filesToCompile.push_back(newFile);
}

void CMakeFile::setProjectName(std::string name)
{
	m_name = name;
}

void CMakeFile::createFile() const
{
	std::stringstream executables;

	executables << "\t${PROJECT_NAME}";
	for(const auto &executable : m_filesToCompile) executables << "\n\t${PROJECT_SOURCE_DIR}/src/" << executable << ".cpp";

	File("CMakeLists.txt", {
		"#Minimum cmake version required to run this text file",
		"cmake_minimum_required(VERSION 3.10)",
		"",
		"# Project name",
		"project(" + m_name + ")",
		"# C++ standard",
		"set(CMAKE_CXX_STANDARD 17)",
		"# Force the C++ standard",
		"set(CMAKE_CXX_STANDARD_REQUIRED True)",
		"# Generate compile commands (this is for vim)",
		"set(CMAKE_EXPORT_COMPILE_COMMANDS On)",
		"",
		"# Find the SDL2 library",
		"find_package(SDL2 REQUIRED)",
		"",
		"# Project configuration file",
		"configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)",
		"",
		"# Create the executable from following cpp files",
		"add_executable(",
		executables.str(),
		")",
		"",
		"# Include these directories in the project",
		"target_include_directories(",
		"	${PROJECT_NAME}",
		"	PUBLIC ${PROJECT_SOURCE_DIR}/include",
		"	PUBLIC ${SDL2_INCLUDE_DIRS}",
		")",
		"",
		"# Libraries to link to the project",
		"target_link_libraries(",
		"	${PROJECT_NAME}",
		"	PUBLIC ${SDL2_LIBRARIES}",
		")",
		"",
		"# Set output directory",
		"set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)",
	}, {}).write();
}

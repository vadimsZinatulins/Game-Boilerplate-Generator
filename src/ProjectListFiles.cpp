#include "generators/ProjectListFiles.h"
#include "utils/File.h"

#include <sstream>

namespace gbg::generators {

void ProjectListFiles::setProjectVersion(std::size_t major, std::size_t minor, std::size_t patch, std::size_t tweak) {
	m_projectMajorVersion = major;
	m_projectMinorVersion = minor;
	m_projectPatchVersion = patch;
	m_projectTweakVersion = tweak;
}

void ProjectListFiles::addFileToCompile(std::string file) {
	m_filesToCompile.push_back(file);
}

void ProjectListFiles::setProjectName(std::string name) {
	m_name = name;
}

void ProjectListFiles::generateFiles() const {
	generateBaseListFile();
	generateSrcListFile();
}

void ProjectListFiles::generateBaseListFile() const {
	auto projectVersion { generateProjectVersion() };

	File("CMakeLists.txt", {
		"#Minimum cmake version required to run this text file",
		"cmake_minimum_required(VERSION 3.20)",
		"",
		"# Project name",
		"project(" + m_name + " " + projectVersion + ")",
		"",
		"# C++ standard",
		"set(CMAKE_CXX_STANDARD 20)",
		"# Force the C++ standard",
		"set(CMAKE_CXX_STANDARD_REQUIRED True)",
		"# Generate compile commands (this is for vim)",
		"set(CMAKE_EXPORT_COMPILE_COMMANDS True)",
		"",
		"add_subdirectory(src)",

	}, {}).write();
}

void ProjectListFiles::generateSrcListFile() const {
	auto sourceFiles { generateSourceFiles() };
	auto findLibraries { generateFindLibraries() };
	auto linkLibraries { generateLinkLibraries() };

	File("src/CMakeLists.txt", {
		findLibraries,
		"# Project configuration file",
		"configure_file(config/config.h.in include/config.h)",
		"",
		"# Create the executable from following cpp files",
		"add_executable(",
		sourceFiles,
		")",
		"",
		findLibraries,
		linkLibraries,
	}, {}).write();
}

std::string ProjectListFiles::generateProjectVersion() const {
	std::stringstream version;

	version << m_projectMajorVersion;

	if(m_projectMinorVersion > 0) {
		version << "." << m_projectMinorVersion;

		if(m_projectPatchVersion > 0) {
			version << "." << m_projectPatchVersion;

			if(m_projectTweakVersion > 0) {
				version << "." << m_projectTweakVersion;
			}
		}
	}
	return version.str();
}

std::string ProjectListFiles::generateSourceFiles() const {
	std::stringstream sourceFiles;

	sourceFiles << "\t${PROJECT_NAME}";
	for(const auto &srcFile : m_filesToCompile) {
	   	sourceFiles << "\n\tsrc/" << srcFile << ".cpp";
	}

	return sourceFiles.str();
}

std::string ProjectListFiles::generateFindLibraries() const {
	std::stringstream findLibraries;
	
	findLibraries << "# Find the SDL2 library\n";
	findLibraries << "find_package(SDL2 REQUIRED)\n";

	if(false) {
		findLibraries << "# Find SDL2_image library\n";
		findLibraries << "find_library(SDL2_IMAGE_LIBRARY SDL2_image)\n";
	}

	return findLibraries.str();
}

std::string ProjectListFiles::generateLinkLibraries() const {
	std::stringstream linkLibraries;

	linkLibraries << "# Libraries to link to the project\n";
	linkLibraries << "target_link_libraries(${PROJECT_NAME}\n";
	linkLibraries << "\tPUBLIC\n";
	linkLibraries << "\t\t${SDL2_LIBRARIES}\n";
	if(false) {
		linkLibraries << "\t\t${SDL2_IMAGE_LIBRARY}\n";
	}
	linkLibraries << ")\n";

	return linkLibraries.str();
}

}

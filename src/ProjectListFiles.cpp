#include "generators/ProjectListFiles.h"
#include "utils/File.h"

#include <sstream>

namespace gbg::generators {

void ProjectListFiles::setProjectName(std::string name) {
	m_name = name;
}

void ProjectListFiles::setWithSDL2ImageExtra(bool flag) {
	m_withSDL2ImageExtra = flag;
}

void ProjectListFiles::setProjectVersion(std::size_t major, std::size_t minor, std::size_t patch, std::size_t tweak) {
	m_projectMajorVersion = major;
	m_projectMinorVersion = minor;
	m_projectPatchVersion = patch;
	m_projectTweakVersion = tweak;
}

void ProjectListFiles::addFileToCompile(std::string file) {
	m_filesToCompile.push_back(file);
}

void ProjectListFiles::generateFiles() const {
	generateBaseListFile();
	generateSrcListFile();
}

void ProjectListFiles::generateBaseListFile() const {
	auto projectVersion { generateProjectVersion() };
	auto fetchContent { generateFetchContent() };

	File("CMakeLists.txt", {
		"#Minimum cmake version required to run this text file",
		"cmake_minimum_required(VERSION 3.20)",
		"",
		"# Project name",
		"project(" + m_name + " VERSION " + projectVersion + ")",
		"",
		"# C++ standard",
		"set(CMAKE_CXX_STANDARD 20)",
		"# Force the C++ standard",
		"set(CMAKE_CXX_STANDARD_REQUIRED True)",
		"# Generate compile commands (this is for vim)",
		"set(CMAKE_EXPORT_COMPILE_COMMANDS True)",
		"",
		fetchContent,
		"",
		"# Project configuration file",
		"configure_file(config/config.h.in \"${PROJECT_SOURCE_DIR}/include/config.h\")",
		"",
		"add_subdirectory(src)",

	}, {}).write();
}

void ProjectListFiles::generateSrcListFile() const {
	auto sourceFiles { generateSourceFiles() };
	auto linkLibraries { generateLinkLibraries() };

	File("src/CMakeLists.txt", {
		sourceFiles,
		"",
		"target_include_directories(${PROJECT_NAME} PRIVATE \"${PROJECT_SOURCE_DIR}/include\")",
		"",
		// findLibraries,
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

	sourceFiles << "# Create the executable from following cpp files\n";
	sourceFiles << "add_executable(${PROJECT_NAME}";

	for(const auto &srcFile : m_filesToCompile) {
	   	sourceFiles << "\n\t" << srcFile << ".cpp";
	}

	sourceFiles << ")";

	return sourceFiles.str();
}

std::string ProjectListFiles::generateFetchContent() const {
	std::stringstream fetchContent;

	fetchContent << "include(FetchContent)\n\n";
	fetchContent << "# Do not install SDL2\n";
	fetchContent << "set(SDL2_DISABLE_INSTALL CACHE BOOL On FORCE)\n";
	fetchContent << "# Build only SDL2 Static Lib\n";
	fetchContent << "set(SDL_SHARED_ENABLED_BY_DEFAULT CACHE BOOL Off FORCE)\n";
	fetchContent << "message(STATUS \"Fetching and configuring SDL2\")\n";
	fetchContent << "FetchContent_Declare(\n";
	fetchContent << "\tSDL2\n";
	fetchContent << "\tGIT_REPOSITORY https://github.com/libsdl-org/SDL.git\n";
	fetchContent << "\tGIT_TAG release-2.28.2  # Change this freely\n";
	fetchContent << ")\n\n";
	fetchContent << "FetchContent_MakeAvailable(SDL2)";

	if(m_withSDL2ImageExtra) {
		fetchContent << "\n\n# Do not install SDL2-image\n";
		fetchContent << "set(SDL2IMAGE_INSTALL CACHE BOOL Off FORCE)\n";
		fetchContent << "# Build only SDL2_image static lib\n";
		fetchContent << "set(BUILD_SHARED_LIBS CACHE BOOL Off FORCE)\n";
		fetchContent << "message(STATUS \"Fetching and configuring SDL2_image\")\n";
		fetchContent << "FetchContent_Declare(\n";
		fetchContent << "\tSDL2_image\n";
		fetchContent << "\tGIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git\n";
		fetchContent << "\tGIT_TAG release-2.6.3  # Change this freely\n";
		fetchContent << ")\n\n";
		fetchContent << "FetchContent_MakeAvailable(SDL2_image)";
	}

	return fetchContent.str();
}

std::string ProjectListFiles::generateLinkLibraries() const {
	std::stringstream linkLibraries;

	linkLibraries << "# Libraries to link to the project\n";
	linkLibraries << "target_link_libraries(${PROJECT_NAME}\n";
	linkLibraries << "\tPUBLIC\n";
	linkLibraries << "\t\tSDL2::SDL2-static\n";
	if(m_withSDL2ImageExtra) {
		linkLibraries << "\t\tSDL2_image::SDL2_image-static\n";
	}
	linkLibraries << ")\n";

	return linkLibraries.str();
}

}

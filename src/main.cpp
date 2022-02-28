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

void generateKeyManager()
{
	std::ofstream header("include/KeyManager.h");

	header << "#pragma once\n\n";
	header << "using Key = unsigned int;\n\n";
	header << "class KeyManager\n{\n";
	header << "public:\n";
	header << "\tstatic KeyManager &getInstance();\n\n";
	header << "\tbool isKeyPressed(Key key) const;\n";
	header << "\tbool isKeyDown(Key key) const;\n";
	header << "\tbool isKeyReleased(Key key) const;\n";
	header << "private:\n";
	header << "\tfriend class Game;\n\n";
	header << "\tclass KeyMap\n\t{\n";
	header << "\tpublic:\n";
	header << "\t\tstatic constexpr int CacheLineSize { 64 };\n";
	header << "\t\tstatic constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };\n\n";
	header << "\t\tvoid operator=(const KeyMap &other);\n\n";
	header << "\t\tvoid insert(Key key);\n";
	header << "\t\tbool contains(Key key);\n";
	header << "\t\tvoid remove(Key key);\n\n";
	header << "\tprivate:\n";
	header << "\t\tKey m_keys[ArraySize];\n";
	header << "\t\tunsigned char m_size { 0 };\n";
	header << "\t};\n\n";
	header << "\tKeyManager() = default;\n";
	header << "\t~KeyManager() = default;\n\n";
	header << "\tvoid update();\n\n";
	header << "\tvoid keyPressed(Key key);\n";
	header << "\tvoid keyReleased(Key key);\n\n";
	header << "\tstatic KeyManager m_instance;\n\n";
	header << "\tKeyMap m_currFrameKeys;\n";
	header << "\tKeyMap m_oldFrameKeys;\n";
	header << "};\n";

	header.close();
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
	generateKeyManager();

	return 0;
}

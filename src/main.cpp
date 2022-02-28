#include "config.h"
#include "workspace.h"
#include "cmakelists.h"
#include "keymanager.h"
#include "game.h"
#include "projectnameclass.h"
#include "mainfile.h"
#include "configfile.h"

#include <iostream>

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

	std::cout << "[1/7] Generating workspace" << std::endl;
	generateWorkspace(projectName);
	std::cout << "[2/7] Generating CMakeLists.txt" << std::endl;
	generateCMakeLists(projectName);
	std::cout << "[3/7] Generating KeyManager class" << std::endl;
	generateKeyManager();
	std::cout << "[4/7] Generating Game class" << std::endl;
	generateGameClass();
	std::cout << "[5/7] Generating " << projectName << " class" << std::endl;
	generateProjectNameClass(projectName);
	std::cout << "[6/7] Generating src/main.cpp" << std::endl;
	generateMain(projectName);
	std::cout << "[7/7] Generating config/config.h.in" << std::endl;
	generateConfigFile(projectName);

	std::cout << "Done! You can now run the following commands:" << std::endl;
	std::cout << "\tcd " << projectName << std::endl;
	std::cout << "\tcmake -E chdir build/ cmake .." << std::endl;
	std::cout << "\tcmake --build build/" << std::endl << std::endl;
	std::cout << "\tbin/" << projectName << std::endl << std::endl;
	std::cout << "And change the both config/config.h.in and CMakeLists.txt files as you want. Have fun!" << std::endl;

	return 0;
}

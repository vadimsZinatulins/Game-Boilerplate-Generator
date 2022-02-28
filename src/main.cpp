#include "config.h"
#include "workspace.h"
#include "cmakelists.h"
#include "keymanager.h"

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

	generateWorkspace(projectName);
	generateCMakeLists(projectName);
	generateKeyManager();

	return 0;
}

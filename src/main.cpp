#include "config.h"

#include <iostream>
#include <string>
#include <filesystem>

void generateWorkspace(const std::string &projectName)
{
	std::filesystem::create_directory(projectName);
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);
	for(const auto &dir : { "bin", "build", "config", "include", "src" }) std::filesystem::create_directory(dir);
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

	return 0;
}

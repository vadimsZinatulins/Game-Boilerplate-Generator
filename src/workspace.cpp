#include "workspace.h"

#include <filesystem>

void generateWorkspace(const std::string &projectName)
{
	std::filesystem::create_directory(projectName);
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);
	for(const auto &dir : { "bin", "build", "config", "include", "src" }) std::filesystem::create_directory(dir);
}

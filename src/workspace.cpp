#include "workspace.h"

#include <filesystem>

namespace gbg::generators {

void generateWorkspace(const std::string &projectName, bool withVulkan) {
	// Create a directory with projects name
	std::filesystem::create_directory(projectName);

	// Go to the created directory
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);

	std::vector<const char*> directories { "src", "src/be", "config", "include", "include/be" };
	if(withVulkan) {
		directories.push_back("include/be/vulkan");
		directories.push_back("src/be/vulkan");
	}

	// Create the following directories
	for(const auto &dir : directories) {
		std::filesystem::create_directory(dir);
	}
}

}


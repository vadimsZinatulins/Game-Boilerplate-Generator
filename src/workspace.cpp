#include "workspace.h"

#include <filesystem>

namespace gbg::generators {

void generateWorkspace(const std::string &projectName) {
	// Create a directory with projects name
	std::filesystem::create_directory(projectName);

	// Go to the created directory
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);

	// Create the following directories
	for(const auto &dir : { "src", "src/config", "src/include", "src/include/be" }) {
		std::filesystem::create_directory(dir);
	}
}

}


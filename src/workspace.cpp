#include "workspace.h"

#include <filesystem>
#include <vector>

namespace gbg::generators {

void generateWorkspace(const std::string &projectName, bool withMathExtra) {
	// Create a directory with projects name
	std::filesystem::create_directory(projectName);

	// Go to the created directory
	std::filesystem::current_path(std::filesystem::current_path().string() + "/" + projectName);

	std::vector<const char*> directories { "src", "src/be", "config", "include", "include/be" };
	if(withMathExtra) {
		directories.push_back("include/be/math");
		directories.push_back("src/be/math");
	}

	// Create the following directories
	for(const auto &dir : directories) {
		std::filesystem::create_directory(dir);
	}
}

}


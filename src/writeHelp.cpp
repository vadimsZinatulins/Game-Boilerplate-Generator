#include "writeHelp.h"
#include "Logger.h"

#include <sstream>

namespace gbg::utils {

void writeHelp() {
	std::stringstream help;

	help << "Usage: gbg --name PROJECT_NAME [OPTIONS...]\n";
	help << "Generates a base game structure that uses SDL2 (and optionally SDL2_Image) ready to build using CMake\n\n";
	help << "List of options:\n";
	help << "\t-n, --name\t\tSpecifies what name for the project to use (mandatory)\n";
	help << "\t    --no-logs\t\tDon't print logs\n";
	help << "\t-h, --help\t\tDisplay help\n";
	help << "\t    --with-vulkan\tGenerates SDL2 project with Vulkan boilerplate setup\n";
	help << "\t    --with-SDL2-image\tInclude SDL2_Image in the project (requires that SDL2_image is installed) if --with-vulkan parameter is not being used\n";

	Log() << help.str();
}

}

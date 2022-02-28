#include "configfile.h"

#include <fstream>

void generateConfigFile(const std::string &projectName)
{
	std::ofstream config("config/config.h.in");

	config << "#pragma once\n\n";
	config << "#define MAJOR_VERSION @" << projectName << "_VERSION_MAJOR@\n";
	config << "#define MINOR_VERSION @" << projectName << "_VERSION_MINOR@\n\n";
	config << "#define SCREEN_TITLE \"" << projectName << "\"\n\n";
	config << "#define SCREEN_WIDTH 800\n";
	config << "#define SCREEN_HEIGHT 600\n\n";
	config << "#define FRAME_CAP 60\n";

	config.close();
}

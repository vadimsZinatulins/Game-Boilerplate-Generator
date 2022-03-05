#include "configfile.h"
#include "utils.h"

void generateConfigFile(const std::string &projectName)
{
	mkfile("config/config.h.in", {
		"#pragma once",
		"",
		"// Set the major version for the project",
		"#define MAJOR_VERSION @" + projectName + "_VERSION_MAJOR@",
		"// Set the minor version for the project",
		"#define MINOR_VERSION @" + projectName + "_VERSION_MINOR@",
		"",
		"// Window title",
		"#define SCREEN_TITLE \"" + projectName + "\"",
		"",
		"// Window width",
		"#define SCREEN_WIDTH 800",
		"// Window height",
		"#define SCREEN_HEIGHT 600",
		"",
		"// Maximum frame rate",
		"#define FRAME_CAP 60"
	});
}

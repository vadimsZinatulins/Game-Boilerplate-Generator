#include "Config.h"
#include "utils/File.h"

void Config::setProjectName(std::string name)
{
	m_projectName = name;
}

void Config::createFile() const
{
	File("config/config.h.in", {
		"#pragma once",
		"",
		"// Set the major version for the project",
		"#define MAJOR_VERSION @Test_VERSION_MAJOR@",
		"// Set the minor version for the project",
		"#define MINOR_VERSION @Test_VERSION_MINOR@",
		"",
		"// Window title",
		"#define SCREEN_TITLE \"" + m_projectName + "\"",
		"",
		"// Window width",
		"#define SCREEN_WIDTH 800",
		"// Window height",
		"#define SCREEN_HEIGHT 600",
		"",
		"// Maximum frame rate",
		"#define FRAME_CAP 60",
	}, {}).write();
}


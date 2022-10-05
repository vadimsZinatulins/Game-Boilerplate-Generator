#include "Config.h"
#include "utils/File.h"

#include <sstream>
#include <string>

namespace gbg::generators {

void Config::setProjectName(std::string name) {
	m_projectName = name;
}

void Config::setWithSDL2ImageExtra(bool flag) {
	m_withSDL2ImageExtra = flag;
}

void Config::createFile() const {
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

std::string Config::generateExtras() const {
	std::stringstream extras;

	if(m_withSDL2ImageExtra) {
		extras << "",
		extras << "// Initializations:\n";
		extras << "// \tJPG = 1\n";
		extras << "// \tPNG = 2\n";
		extras << "// \tTIF = 4\n";
		extras << "// \tWEBP = 8\n";
		extras << "// These can be ORed together (example: 1 | 4)\n";
		extras << "#define IMAGE_INIT 2";
	}

	return extras.str();
}

}

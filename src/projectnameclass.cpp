#include "projectnameclass.h"
#include "utils.h"

void generateProjectNameClassHeader(const std::string &projectName)
{
	mkfile("include/" + projectName + ".h", {
		"#pragma once",
		"",
		"#include \"BE/Game.h\"",
		"",
		"class " + projectName + " final : public BE::Game<" + projectName + ">",
		"{",
		"public:",
		"	" + projectName + "() = default;",
		"	~" + projectName + "() = default;",
		"private:",
		"	friend class BE::Game<" + projectName + ">;",
		"",
		"	void initialize();",
		"	void shutdown();",
		"};"
	});
}

void generateProjectNameClassSource(const std::string &projectName)
{
	mkfile("src/" + projectName + ".cpp", {
		"#include \"" + projectName + ".h\"",
		"#include \"MainMenuScene.h\"",
		"#include \"BE/SceneManager.h\"",
		"",
		"#include <SDL2/SDL.h>",
		"",
		"void " + projectName + "::initialize()",
		"{",
		"	BE::SceneManager::getInstance().pushScene<MainMenuScene>();",
		"}",
		"",
		"void " + projectName + "::shutdown()",
		"{",
		"",
		"}",
		"",
	});
}

void generateProjectNameClass(const std::string &projectName)
{
	generateProjectNameClassHeader(projectName);
	generateProjectNameClassSource(projectName);
}

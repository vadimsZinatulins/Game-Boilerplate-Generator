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
		"	void update();",
		"	void render(SDL_Renderer *renderer);",
		"};"
	});
}

void generateProjectNameClassSource(const std::string &projectName)
{
	mkfile("src/" + projectName + ".cpp", {
		"#include \"" + projectName + ".h\"",
		"",
		"#include <SDL2/SDL.h>",
		"",
		"void " + projectName + "::initialize()",
		"{",
		"",
		"}",
		"",
		"void " + projectName + "::shutdown()",
		"{",
		"",
		"}",
		"",
		"void " + projectName + "::update()",
		"{",
		"",
		"}",
		"",
		"void " + projectName + "::render(SDL_Renderer *renderer)"
		"{",
		"",
		"}"
	});
}

void generateProjectNameClass(const std::string &projectName)
{
	generateProjectNameClassHeader(projectName);
	generateProjectNameClassSource(projectName);
}

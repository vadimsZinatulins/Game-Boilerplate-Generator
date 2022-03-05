#include "projectnameclass.h"
#include "utils.h"

void generateProjectNameClassHeader(const std::string &projectName)
{
	mkfile("include/" + projectName + ".h", {
		"#pragma once",
		"",
		"#include \"Game.h\"",
		"",
		"class " + projectName + " final : public Game",
		"{",
		"public:",
		"	" + projectName + "() = default;",
		"	~" + projectName + "() = default;",
		"",
		"	void initialize() override;",
		"	void shutdown() override;",
		"	void update() override;",
		"	void render(SDL_Renderer *renderer) override;",
		"private:",
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
		"}",
		"",
	});
}

void generateProjectNameClass(const std::string &projectName)
{
	generateProjectNameClassHeader(projectName);
	generateProjectNameClassSource(projectName);
}

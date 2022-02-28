#include "projectnameclass.h"

#include <fstream>

void generateProjectNameClassHeader(const std::string &projectName)
{
	std::ofstream header("include/" + projectName + ".h");

	header << "#pragma once\n\n";
	header << "#include \"Game.h\"\n\n";
	header << "class " << projectName << " final : public Game\n{\n";
	header << "public:\n";
	header << "\t" << projectName << "() = default;\n";
	header << "\t~" << projectName << "() = default;\n\n";
	header << "\tvoid initialize() override;\n";
	header << "\tvoid shutdown() override;\n";
	header << "\tvoid update(float deltaTime) override;\n";
	header << "\tvoid render(SDL_Renderer *renderer) override;\n\n";
	header << "private:\n\n";
	header << "};\n";

	header.close();
}

void generateProjectNameClassSource(const std::string &projectName)
{
	std::ofstream src("src/" + projectName + ".cpp");

	src << "#include \"" << projectName << ".h\"\n\n";
	src << "#include <SDL2/SDL.h>\n\n";
	src << "void " << projectName << "::initialize()\n{\n\n}\n\n";
	src << "void " << projectName << "::shutdown()\n{\n\n}\n\n";
	src << "void " << projectName << "::update(float deltaTime)\n{\n\n}\n\n";
	src << "void " << projectName << "::render(SDL_Renderer *renderer)\n{\n\n}\n\n";

	src.close();
}

void generateProjectNameClass(const std::string &projectName)
{
	generateProjectNameClassHeader(projectName);
	generateProjectNameClassSource(projectName);
}

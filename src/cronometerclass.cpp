#include "cronometerclass.h"

#include <fstream>

void generateCronoHeader()
{
	std::ofstream header("include/Cronometer.h");

	header << "#pragma once\n\n";
	header << "class Cronometer\n{\n";
	header << "public:\n";
	header << "\tCronometer() = default;\n";
	header << "\t~Cronometer() = default;\n\n";
	header << "\tvoid start();\n";
	header << "\tvoid stop();\n";
	header << "\tvoid resume();\n\n";
	header << "\tunsigned int getSeconds() const;\n";
	header << "\tunsigned int getMilliseconds() const;\n\n";
	header << "\tbool isRunning() const;\n";
	header << "private:\n";
	header << "\tunsigned int m_startTime { 0 };\n";
	header << "\tunsigned int m_stopTime { 0 };\n\n";
	header << "\tbool m_isRunning { false };\n";
	header << "};\n";

	header.close();
}

void generateCronoSource()
{
	std::ofstream src("src/Cronometer.cpp");

	src << "#include \"Cronometer.h\"\n\n";
	src << "#include <SDL2/SDL.h>\n\n";
	src << "void Cronometer::start()\n{\n";
	src << "\tif(!m_isRunning)\n{\n";
	src << "\t\tm_isRunning = true;\n";
	src << "\t\tm_stopTime = 0;\n\n";
	src << "\t\tm_startTime = SDL_GetTicks();\n";
	src << "\t}\n";
	src << "}\n\n";
	src << "void Cronometer::stop()\n{\n";
	src << "\tif(m_isRunning)\n{\n";
	src << "\t\tm_stopTime = SDL_GetTicks();\n\n";
	src << "\t\tm_isRunning = false;\n";
	src << "\t}\n";
	src << "}\n\n";
	src << "void Cronometer::resume()\n{\n";
	src << "\tif(!m_isRunning)\n{\n";
	src << "\t\tm_startTime += SDL_GetTicks() - m_stopTime;\n";
	src << "\t\tm_stopTime = 0;\n\n";
	src << "\t\tm_isRunning = true;\n";
	src << "\t}\n";
	src << "}\n\n";
	src << "unsigned int Cronometer::getSeconds() const\n{\n";
	src << "\treturn ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;\n";
	src << "}\n\n";
	src << "unsigned int Cronometer::getMilliseconds() const\n{\n";
	src << "\treturn (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;\n";
	src << "}\n\n";
	src << "bool Cronometer::isRunning() const\n{\n";
	src << "\treturn m_isRunning;\n";
	src << "}\n\n";

	src.close();
}

void generateCronometerClass()
{
	generateCronoHeader();
	generateCronoSource();
}

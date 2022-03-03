#include "time.h"

#include <fstream>

void generateTimeHeader()
{
	std::ofstream header("include/Time.h");
	
	header << "#pragma once\n\n";
	header << "class Time\n{\n";
	header << "public:\n";
	header << "\tstatic inline unsigned int getTicks() { return m_ticks; }\n\n";
	header << "\tstatic inline float getDeltaTime() { return m_deltaTime; }\n";
	header << "private:\n";
	header << "\tfriend class Game;\n\n";
	header << "\tTime();\n";
	header << "\t~Time();\n\n";
	header << "\tstatic unsigned int m_ticks;\n";
	header << "\tstatic float m_deltaTime;\n";
	header << "};\n";

	header.close();
}

void generateTimeSource()
{
	std::ofstream src("src/Time.cpp");

	src << "#include \"Time.h\"\n";
	src << "#include \"config.h\"\n\n";
	src << "#include <SDL2/SDL.h>\n\n";
	src << "constexpr unsigned int MinTicksPerFrame = 1000 / FRAME_CAP;\n\n";
	src << "unsigned int Time::m_ticks = 0;\n\n";
	src << "float Time::m_deltaTime = 0.0f;\n\n";
	src << "Time::Time()\n{\n"; 
	src << "\tunsigned int ticks = SDL_GetTicks();\n";
	src << "\tm_deltaTime = (float)(ticks - m_ticks) / 1000.0f;\n";
	src << "\tm_ticks = ticks;\n";
	src << "}\n\n";
	src << "Time::~Time()\n{\n"; 
	src << "\tunsigned int frameTicks = SDL_GetTicks() - m_ticks;\n";
	src << "\tif(frameTicks < MinTicksPerFrame) SDL_Delay(MinTicksPerFrame - frameTicks);\n";
	src << "}\n\n";

	src.close();
}

void generateTimeClass()
{
	generateTimeHeader();
	generateTimeSource();
}

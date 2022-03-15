#include "time.h"
#include "utils.h"

void generateTimeHeader()
{
	mkfile("include/BE/Time.h", {
		"#pragma once",
		"",
		"namespace BE",
		"{",
		"",
		"class Time",
		"{",
		"public:",
		"	static inline unsigned int getTicks() { return m_ticks; }",
		"	static inline float getDeltaTime() { return m_deltaTime; }",
		"private:",
		"	template<typename T>",
		"	friend class Game;",
		"",
		"	Time();",
		"	~Time();",
		"",
		"	static unsigned int m_ticks;",
		"	static float m_deltaTime;",
		"};",
		"",
		"}"
	});
}

void generateTimeSource()
{
	mkfile("src/BE/Time.cpp", {
		"#include \"BE/Time.h\"",
		"#include \"config.h\"",
		"",
		"#include <SDL2/SDL.h>",
		"",
		"namespace BE",
		"{",
		"",
		"constexpr unsigned int MinTicksPerFrame = 1000 / FRAME_CAP;",
		"",
		"unsigned int Time::m_ticks = 0;",
		"float Time::m_deltaTime = 0.0f;",
		"",
		"Time::Time()", 
		"{", 
		"	unsigned int ticks = SDL_GetTicks();",
		"	m_deltaTime = (float)(ticks - m_ticks) / 1000.0f;",
		"	m_ticks = ticks;",
		"}",
		"",
		"Time::~Time(){", 
		"	unsigned int frameTicks = SDL_GetTicks() - m_ticks;",
		"	if(frameTicks < MinTicksPerFrame) SDL_Delay(MinTicksPerFrame - frameTicks);",
		"}",
		"",
		"}"
	});
}

void generateTimeClass()
{
	generateTimeHeader();
	generateTimeSource();
}

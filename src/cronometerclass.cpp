#include "cronometerclass.h"
#include "utils.h"

void generateCronoHeader()
{
	mkfile("include/BE/Cronometer.h", {
		"#pragma once",
		"",
		"namespace BE",
		"{",
		"",
		"class Cronometer",
		"{",
		"public:",
		"	Cronometer() = default;",
		"	~Cronometer() = default;",
		"	void start();",
		"	void stop();",
		"	void resume();",
		"	void restart();",
		"",
		"	unsigned int getSeconds() const;",
		"	unsigned int getMilliseconds() const;",
		"",
		"	bool isRunning() const;",
		"private:",
		"	unsigned int m_startTime { 0 };",
		"	unsigned int m_stopTime { 0 };",
		"",
		"	bool m_isRunning { false };",
		"};",
		"",
		"}",
	});
}

void generateCronoSource()
{
	mkfile("src/BE/Cronometer.cpp", {
		"#include \"BE/Cronometer.h\"",
		"",
		"#include <SDL2/SDL.h>",
		"",
		"namespace BE",
		"{",
		"",
		"void Cronometer::start()",
		"{",
		"	if(!m_isRunning)",
		"	{",
		"		m_isRunning = true;",
		"		m_startTime = SDL_GetTicks();",
		"	}",
		"}",
		"",
		"void Cronometer::stop()",
		"{",
		"	if(m_isRunning)",
		"	{",
		"		m_stopTime = SDL_GetTicks();",
		"",
		"		m_isRunning = false;",
		"	}",
		"}",
		"",
		"void Cronometer::resume()",
		"{",
		"	if(!m_isRunning)",
		"	{",
		"		m_startTime += SDL_GetTicks() - m_stopTime;",
		"		m_isRunning = true;",
		"	}",
		"}",
		"",
		"void Cronometer::restart()",
		"{",
		"	m_isRunning = true;",
		"	m_startTime = SDL_GetTicks();",
		"}",
		"",
		"unsigned int Cronometer::getSeconds() const",
		"{",
		"	return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;",
		"}",
		"",
		"unsigned int Cronometer::getMilliseconds() const",
		"{",
		"	return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;",
		"}",
		"",
		"bool Cronometer::isRunning() const",
		"{",
		"	return m_isRunning;",
		"}",
		"",
		"}"
	});
}

void generateCronometerClass()
{
	generateCronoHeader();
	generateCronoSource();
}

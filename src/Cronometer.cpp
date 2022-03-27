#include "Cronometer.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"

void Cronometer::generate() const
{
	generateHeader();
	generateSource();
}

void Cronometer::generateHeader() const
{
	File("include/BE/" + m_className + ".h", { "#pragma once\n" }, {
		Namespace("BE", {
			Class(m_className, {
				m_className + " = default;",
				"~" + m_className + " = default;",
				"",
				"void start();",
				"void stop();",
				"void resume();",
				"void restart();",
				"",
				"unsigned int getSeconds(); const",
				"unsigned int getMilliseconds(); const",
				"",
				"bool isRunning(); const",
			}, {}, {
				"unsigned int m_startTime { 0 };",
				"unsigned int m_stopTime { 0 };",
				"",
				"bool m_isRunning { false };"
			})
		})
	}).write();
}

void Cronometer::generateSource() const
{
	File("src/BE/" + m_className + ".cpp", {
		"#include \"" + m_className + ".h\"\n",
		"#include <SDL2/SDL.h>"
	}, {
		Namespace("BE", {
			Function("", "void " + m_className + "::start()", {
				IfStatement("!m_isRunning", {
					"m_isRunning = true;",
					"m_startTime = SDL_GetTicks();"
				})
			}),
			"",
			Function("", "void " + m_className + "::stop()", {
				IfStatement("m_isRunning", {
					"m_stopTime = SDL_GetTicks();",
					"m_isRunning = false;"
				})
			}),
			"",
			Function("", "void " + m_className + "::resume()", {
				IfStatement("m_isRunning", {
					"m_startTime += SDL_GetTicks() - m_stopTime;",
					"m_isRunning = true;"
				})
			}),
			"",
			Function("", "void " + m_className + "::restart()", {
				"m_isRunning = true;",
				"m_startTime = SDL_GetTicks();"
			}),
			"",
			Function("", "unsigned int " + m_className + "::getSeconds()", {
				"return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;",
			}),
			"",
			Function("", "unsigned int " + m_className + "::getMilliseconds()", {
				"return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;"
			}),
			"",
			Function("", "bool " + m_className + "::isRunning()", {
				"return m_isRunning;"
			})
		})
	}).write();
}


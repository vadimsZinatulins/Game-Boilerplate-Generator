#include "Cronometer.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"

namespace gbg::generators {

void Cronometer::generate() const {
	generateHeader();
	generateSource();
}

void Cronometer::generateHeader() const {
	File("include/be/Cronometer.h", { "#pragma once\n" }, {
		Namespace("be", {
			Class("Cronometer", {
				"Cronometer() = default;",
				"~Cronometer() = default;",
				"",
				"void start();",
				"void stop();",
				"void resume();",
				"void restart();",
				"",
				"unsigned int getSeconds() const;",
				"unsigned int getMilliseconds() const;",
				"",
				"bool isRunning() const;",
			}, {}, {
				"unsigned int m_startTime { 0 };",
				"unsigned int m_stopTime { 0 };",
				"",
				"bool m_isRunning { false };"
			})
		})
	}).write();
}

void Cronometer::generateSource() const {
	File("src/be/Cronometer.cpp", {
		"#include \"be/Cronometer.h\"",
		"",
		"#include <SDL.h>"
	}, {
		Namespace("be", {
			Function("", "void Cronometer::start()", {
				IfStatement("!m_isRunning", {
					"m_isRunning = true;",
					"m_startTime = SDL_GetTicks();"
				})
			}),
			"",
			Function("", "void Cronometer::stop()", {
				IfStatement("m_isRunning", {
					"m_stopTime = SDL_GetTicks();",
					"m_isRunning = false;"
				})
			}),
			"",
			Function("", "void Cronometer::resume()", {
				IfStatement("m_isRunning", {
					"m_startTime += SDL_GetTicks() - m_stopTime;",
					"m_isRunning = true;"
				})
			}),
			"",
			Function("", "void Cronometer::restart()", {
				"m_isRunning = true;",
				"m_startTime = SDL_GetTicks();"
			}),
			"",
			Function("", "unsigned int Cronometer::getSeconds() const", {
				"return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;",
			}),
			"",
			Function("", "unsigned int Cronometer::getMilliseconds() const", {
				"return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;"
			}),
			"",
			Function("", "bool Cronometer::isRunning() const", {
				"return m_isRunning;"
			})
		})
	}).write();
}

}

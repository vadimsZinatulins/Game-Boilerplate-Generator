#include "Time.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/Namespace.h"

namespace gbg::generators {

void Time::generate() const {
	generateHeader();
	generateSource();
}

void Time::generateHeader() const {
	File("include/be/Time.h", { "#pragma once", "" }, {
		Namespace("be", {
			Class("Time", {
				"static inline unsigned int getTicks() { return m_ticks; }",
				"static inline float getDeltaTime() { return m_deltaTime; }"
			}, {}, {
				"template<typename T>",
				"friend class Game;",
				"",
				"Time();",
				"~Time();",
				"",
				"static unsigned int m_ticks;",
				"static float m_deltaTime;"
			})
		})
	}).write();
}

void Time::generateSource() const {
	File("src/be/Time.cpp", { 
		"#include \"be/Time.h\"",
		"#include \"config.h\"",
		"",
		"#include <SDL2/SDL.h>"
	}, {
		Namespace("be", {
			"constexpr unsigned int MinTicksPerFrame = 1000 / FRAME_CAP;",
			"",
			"unsigned int Time::m_ticks = 0;",
			"float Time::m_deltaTime = 0.0f;",
			"",
			Function("", "Time::Time()", {
				"unsigned int ticks = SDL_GetTicks();",
				"m_deltaTime = (float)(ticks - m_ticks) / 1000.0f;",
				"m_ticks = ticks;"
			}),
			"",
			Function("", "Time::~Time()", {
				"unsigned int frameTicks = SDL_GetTicks() - m_ticks;",
				"if(frameTicks < MinTicksPerFrame) SDL_Delay(MinTicksPerFrame - frameTicks);"
			})
		})
	}).write();
}

}

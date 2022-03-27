#include "Time.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/Namespace.h"

Time::Time()
{
	m_class.addAttribute("static inline unsigned int getTicks() { return m_ticks; }", Class::Modifiers::Public);
	m_class.addAttribute("static inline float getDeltaTime() { return m_deltaTime; }", Class::Modifiers::Public);

	m_class.addAttribute("static unsigned int m_ticks;", Class::Modifiers::Private);
	m_class.addAttribute("static float m_deltaTime;\n", Class::Modifiers::Private);

	m_class.addAttribute("template<typename T>", Class::Modifiers::Private);
	m_class.addAttribute("friend class Game;", Class::Modifiers::Private);

	{
		Function constructor("", "", "Time()", "", {
			"unsigned int ticks = SDL_GetTicks();",
			"m_deltaTime = (float)(ticks - m_ticks) / 1000.0f;",
			"m_ticks = ticks;"
		});

		m_class.addMethod(constructor, Class::Modifiers::Private);
	}

	{
		Function destructor("", "", "~Time()", "", {
			"unsigned int frameTicks = SDL_GetTicks() - m_ticks;",
			"if(frameTicks < MinTicksPerFrame) SDL_Delay(MinTicksPerFrame - frameTicks);"
		});

		m_class.addMethod(destructor, Class::Modifiers::Private);
	}
}


Time::~Time()
{

}

void Time::generate() const
{
	generateHeader();
	generateSource();
}

void Time::generateHeader() const
{
	Namespace ns("BE", { m_class.definition() });

	File("include/BE/Time.h", { "#pragma once\n" }, { ns }).write();
}

void Time::generateSource() const
{
	Namespace ns("BE", { 
		"constexpr unsigned int MinTicksPerFrame = 1000 / FRAME_CAP;\n", 
		"unsigned int Time::m_ticks = 0;",
		"float Time::m_deltaTime = 0.0f;\n",
		m_class.declaration() 
	});

	File("src/BE/Time.cpp", { 
		"#include \"BE/Time.h\"",
		"#include \"config.h\"\n",
		"#include <SDL2/SDL.h>"
	}, { ns }).write();
}


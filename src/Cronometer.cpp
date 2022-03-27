#include "Cronometer.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/IfStatement.h"
#include "utils/Namespace.h"

Cronometer::Cronometer()
{
	m_class.addAttribute("Cronometer() = default;", Class::Modifiers::Private);
	m_class.addAttribute("~Cronometer() = default;", Class::Modifiers::Private);

	m_class.addAttribute("unsigned int m_startTime { 0 };", Class::Modifiers::Private);
	m_class.addAttribute("unsigned int m_stopTime { 0 }\n;", Class::Modifiers::Private);

	m_class.addAttribute("bool m_isRunning { false };", Class::Modifiers::Private);

	{
		Function start("", "void", "start()", "", {
			IfStatement("!m_isRunning", {
				"m_isRunning = true;",
				"m_startTime = SDL_GetTicks();"
			})
		});

		m_class.addMethod(start, Class::Modifiers::Public);
	}

	{
		Function stop("", "void", "stop()", "", {
			IfStatement("m_isRunning", {
				"m_stopTime = SDL_GetTicks();",
				"m_isRunning = false;"
			})
		});

		m_class.addMethod(stop, Class::Modifiers::Public);
	}

	{
		Function resume("", "void", "resume()", "", {
			IfStatement("!m_isRunning", {
				"m_startTime += SDL_GetTicks() - m_stopTime;",
				"m_isRunning = true;"
			})
		});

		m_class.addMethod(resume, Class::Modifiers::Public);
	}

	{
		Function restart("", "void", "restart()", "", {
			"m_isRunning = true;",
			"m_startTime = SDL_GetTicks();"
		});

		m_class.addMethod(restart, Class::Modifiers::Public);
	}

	{
		Function getSeconds("", "unsigned int", "getSeconds() const", "", {
			"return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;"
		});

		m_class.addMethod(getSeconds, Class::Modifiers::Public);
	}

	{
		Function getMilliseconds("", "unsigned int", "getMilliseconds() const", "", {
			"return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;"
		});

		m_class.addMethod(getMilliseconds, Class::Modifiers::Public);
	}

	{
		Function isRunning("", "bool", "isRunning() const", "", { "return m_isRunning;" });

		m_class.addMethod(isRunning, Class::Modifiers::Public);
	}
}

Cronometer::~Cronometer()
{

}

void Cronometer::generate() const
{
	generateHeader();
	generateSource();
}

void Cronometer::generateHeader() const
{
	Namespace ns("BE", { m_class.definition() });

	File("include/BE/Cronometer.h", { "#pragma once\n" }, { ns }).write();
}

void Cronometer::generateSource() const
{
	Namespace ns("BE", { m_class.declaration() });

	File("src/BE/Cronometer.cpp", {
		"#include \"BE/Cronometer.h\"\n",
		"#include <SDL2/SDL.h>"
	}, { ns }).write();
}


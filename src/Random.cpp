#include "Random.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/Namespace.h"

Random::Random() 
{ 
	m_class.addAttribute("Random(int seed);", Class::Modifiers::Public);
	m_class.addAttribute("Random();", Class::Modifiers::Public);
	m_class.addAttribute("~Random();", Class::Modifiers::Public);
	m_class.addAttribute("std::mt19937 m_engine;", Class::Modifiers::Private);

	{
		Function nextInt("", "int", "nextInt()", "", { "return nextInt(0, std::numeric_limits<int>::max());" });
		m_class.addMethod(nextInt, Class::Modifiers::Public);
	}

	{
		Function nextInt("", "int", "nextInt(int max)", "", { "return nextInt(0, max);"});
		m_class.addMethod(nextInt, Class::Modifiers::Public);
	}

	{
		Function nextInt("", "int", "nextInt(int min, int max)", "", { "return std::uniform_int_distribution<int>(min, max)(m_engine);" });
		m_class.addMethod(nextInt, Class::Modifiers::Public);
	}

	{
		Function nextFloat("", "float", "nextFloat()", "", { "return nextFloat(0, std::numeric_limits<float>::max());" });
		m_class.addMethod(nextFloat, Class::Modifiers::Public);
	}

	{
		Function nextFloat("", "float", "nextFloat(float max)", "", { "return nextFloat(0, max);" });
		m_class.addMethod(nextFloat, Class::Modifiers::Public);
	}

	{
		Function nextFloat("", "float", "nextFloat(float min, float max)", "", { "return std::uniform_real_distribution<float>(min, max)(m_engine);" });
		m_class.addMethod(nextFloat, Class::Modifiers::Public);
	}
}

Random::~Random() 
{

}

void Random::generate() const
{
	generateHeader();
	generateSource();
}

void Random::generateHeader() const
{
	Namespace ns("BE", { m_class.definition() });

	File("include/BE/Random.h", { "#pragma once\n", "#include <random>" }, { ns }).write();
}

void Random::generateSource() const
{
	Namespace ns("BE", { 
		"Random::Random(int seed) : m_engine(seed) { }",
		"Random::Random() : m_engine(std::random_device()()) { }",
		"Random::~Random() { }\n",
		m_class.declaration() 
	});

	File("src/BE/Random.cpp", {
		"#include \"BE/Random.h\"\n",
		"#include <limits>",
	}, { ns }).write();
}

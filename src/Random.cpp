#include "Random.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/Namespace.h"

void Random::generate() const
{
	generateHeader();
	generateSource();
}

void Random::generateHeader() const
{
	File("include/BE/" + m_className + ".h", {
		"#pragma once\n",
		"#include <random>"
	}, {
		Namespace("BE", {
			Class(m_className, {
				"Random(int seed);",
				"Random();",
				"~Random();",
				"",
				"int nextInt();",
				"int nextInt(int max);",
				"int nextInt(int min, int max);",
				"",
				"float nextFloat();",
				"float nextFloat(float max);",
				"float nextFloat(float min, float max);"
			}, {}, { "std::mt19937 m_engine;" })
		})
	}).write();
}

void Random::generateSource() const
{
	File("src/BE/" + m_className + ".cpp", { 
		"#include \"" + m_className + ".h\"\n"
		"#include <limits>",
	}, {
		"Random::Random(int seed) : m_engine(seed) { }",
		"Random::Random() : m_engine(std::random_device()()) { }",
		"Random::~Random() { }",
		"",
		"int Random::nextInt() { return nextInt(0, std::numeric_limits<int>::max()); }",
		"int Random::nextInt(int max) { return nextInt(0, max); }",
		"int Random::nextInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(m_engine); }",
		"",
		"float Random::nextFloat() { return nextFloat(0, std::numeric_limits<float>::max()); }",
		"float Random::nextFloat(float max) { return nextFloat(0, max); }",
		"float Random::nextFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(m_engine); }"
	}).write();
}

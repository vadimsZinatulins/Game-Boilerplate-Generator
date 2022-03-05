#include "randomclass.h"
#include "utils.h"

void generateRandomHeader()
{
	mkfile("include/Random.h", {
		"#pragma once",
		"",
		"#include <random>",
		"",
		"class Random{",
		"public:",
		"	Random(int seed);",
		"	Random();",
		"	~Random();",
		"",
		"	int nextInt();",
		"	int nextInt(int max);",
		"	int nextInt(int min, int max);",
		"",
		"	float nextFloat();",
		"	float nextFloat(float max);",
		"	float nextFloat(float min, float max);",
		"private:",
		"	std::mt19937 m_engine;",
		"};"
	});
}

void generateRandomSource()
{
	mkfile("src/Random.cpp", {
		"#include \"Random.h\"",
		"",
		"#include <limits>",
		"#include <random>",
		"",
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
		"float Random::nextFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(m_engine); }",
	});
}

void generateRandomClass()
{
	generateRandomHeader();
	generateRandomSource();
}

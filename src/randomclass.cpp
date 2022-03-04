#include "randomclass.h"

#include <fstream>

void generateRandomHeader()
{
	std::ofstream header("include/Random.h");

	header << "#pragma once\n\n";
	header << "#include <random>\n\n";
	header << "class Random\n{\n";
	header << "public:\n";
	header << "\tRandom(int seed);\n";
	header << "\tRandom();\n";
	header << "\t~Random();\n\n";
	header << "\tint nextInt();\n";
	header << "\tint nextInt(int max);\n";
	header << "\tint nextInt(int min, int max);\n\n";
	header << "\tint nextFloat();\n";
	header << "\tint nextFloat(float max);\n";
	header << "\tint nextFloat(float min, float max);\n";
	header << "private:\n";
	header << "\tstd::mt19937 m_engine;\n";
	header << "};\n";

	header.close();
}

void generateRandomSource()
{
	std::ofstream src("src/Random.cpp");

	src << "#include \"Random.h\"\n\n";
	src << "#include <limits>\n";
	src << "#include <random>\n\n";
	src << "Random::Random(int seed) : m_engine(seed) { }\n";
	src << "Random::Random() : m_engine(std::random_device()()) { }\n";
	src << "Random::~Random() { }\n\n";
	src << "int Random::nextInt() { return nextInt(0, std::numeric_limits<int>::max()); }\n";
	src << "int Random::nextInt(int max) { return nextInt(0, max); }\n";
	src << "int Random::nextInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(m_engine); }\n\n";
	src << "int Random::nextFloat() { return nextFloat(0, std::numeric_limits<float>::max()); }\n";
	src << "int Random::nextFloat(float max) { return nextFloat(0, max); }\n";
	src << "int Random::nextFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(m_engine); }\n";

	src.close();
}

void generateRandomClass()
{
	generateRandomHeader();
	generateRandomSource();
}

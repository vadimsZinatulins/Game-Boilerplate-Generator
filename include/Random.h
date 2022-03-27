#pragma once

#include <string>

class Random
{
public:
	Random() = default;
	~Random() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "Random" };
};

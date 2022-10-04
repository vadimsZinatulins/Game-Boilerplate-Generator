#pragma once

#include <string>

class Cronometer
{
public:
	Cronometer() = default;
	~Cronometer() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "Cronometer" };
};

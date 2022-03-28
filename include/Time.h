#pragma once

#include <string>

class Time
{
public:
	Time() = default;
	~Time() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "Time" };
};

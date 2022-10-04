#pragma once

#include <string>

class MouseManager
{
public:
	MouseManager() = default;
	~MouseManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "MouseManager" };
};

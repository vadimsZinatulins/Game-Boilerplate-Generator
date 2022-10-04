#pragma once

#include <string>

class KeyManager
{
public:
	KeyManager() = default;
	~KeyManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "KeyManager" };
};

#pragma once

#include <string>

class Game
{
public:
	Game() = default;
	~Game() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "Game" };
};

#pragma once

#include <string>

class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager() = default;

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_className { "TextureManager" };
};

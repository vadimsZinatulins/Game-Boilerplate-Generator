#pragma once

#include <string>

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	void generate() const;
private:
	void generateSceneManagerHeader() const;
	void generateSceneManagerSource() const;

	void generateSceneHeader() const;

	std::string m_className { "SceneManager" };
};

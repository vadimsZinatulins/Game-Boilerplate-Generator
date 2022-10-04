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

	void generateMainMenuSceneHeader() const;
	void generateMainMenuSceneSource() const;

	std::string m_className { "SceneManager" };
};

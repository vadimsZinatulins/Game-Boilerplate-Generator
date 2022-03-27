#pragma once

#include "utils/Class.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void generate() const;
private:
	void generateSceneManagerHeader() const;
	void generateSceneManagerSource() const;

	void generateSceneHeader() const;
	void generateSceneSource() const;

	Class m_class { "SceneManager" };
};

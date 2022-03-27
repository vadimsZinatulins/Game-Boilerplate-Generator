#pragma once

#include "utils/Class.h"

#include <string>

class MouseManager
{
public:
	MouseManager();
	~MouseManager();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	Class m_class { "MouseManager" };
};

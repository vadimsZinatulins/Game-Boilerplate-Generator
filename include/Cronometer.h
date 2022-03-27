#pragma once

#include "utils/Class.h"
class Cronometer
{
public:
	Cronometer();
	~Cronometer();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	Class m_class { "Cronometer" };
};

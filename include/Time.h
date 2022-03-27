#pragma once

#include "utils/Class.h"

class Time
{
public:
	Time();
	~Time();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	Class m_class { "Time" };
};

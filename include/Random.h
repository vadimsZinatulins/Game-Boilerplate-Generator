#pragma once

#include "utils/Class.h"

class Random
{
public:
	Random();
	~Random();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	Class m_class { "Random" };
};

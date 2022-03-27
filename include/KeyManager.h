#pragma once

#include "utils/Class.h"

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	Class m_class { "KeyManager" };
};

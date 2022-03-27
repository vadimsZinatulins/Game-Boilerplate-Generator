#pragma once

#include "utils/Conditional.h"
#include <sstream>

struct WhileStatement : public Conditional
{
	WhileStatement(Instruction condition, WritableContent body) : 
		Conditional("while", std::move(condition), std::move(body))
	{ }

	~WhileStatement() { }
};

template<>
void write(const WhileStatement &whileStatement, std::stringstream &out, std::size_t position);

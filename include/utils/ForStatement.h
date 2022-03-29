#pragma once

#include "utils/Conditional.h"
#include <sstream>

struct ForStatement : public Conditional
{
	ForStatement(Instruction initialization, Instruction condition, Instruction increment, WritableContent body);
	ForStatement(Instruction condition, WritableContent body);

	~ForStatement();
};

template<>
void write(const ForStatement &forStatement, std::stringstream &out, std::size_t position);

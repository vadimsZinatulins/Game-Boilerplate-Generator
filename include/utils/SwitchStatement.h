#pragma once

#include "utils/Conditional.h"
#include "utils/WritableContent.h"

#include <sstream>

struct SwitchStatement : public Conditional
{
	SwitchStatement(Instruction condition, WritableContent body);
	~SwitchStatement();
};

template<>
void write(const SwitchStatement &switchStatement, std::stringstream &out, std::size_t position);

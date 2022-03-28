#pragma once

#include "utils/Conditional.h"
#include "utils/WritableContent.h"
#include <sstream>

struct SwitchStatement : public Conditional
{
	SwitchStatement(Instruction condition, WritableContent body) : 
		Conditional("switch", std::move(condition), std::move(body))
	{ }

	~SwitchStatement() { }
};

template<>
void write(const SwitchStatement &ifStatement, std::stringstream &out, std::size_t position);

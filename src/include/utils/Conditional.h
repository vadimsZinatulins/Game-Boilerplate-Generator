#pragma once

#include "utils/core/Writer.h"
#include "utils/Instruction.h"
#include "utils/WritableContent.h"

#include <string>

struct Conditional
{
	Conditional(Instruction signature, Instruction condition, WritableContent body);
	virtual ~Conditional();

	Instruction m_condition;
	WritableContent m_body;
};

template<>
void write(const Conditional &conditional, std::stringstream &out, std::size_t position);


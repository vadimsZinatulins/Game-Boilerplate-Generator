#pragma once

#include "utils/core/Writer.h"
#include "utils/Instruction.h"
#include "utils/WritableContent.h"

#include <sstream>

struct Case
{
	Case(Instruction condition, WritableContent body);
	~Case();

	Instruction m_condition;
	WritableContent m_body;
};

template<>
void write(const Case &caseStatement, std::stringstream &out, std::size_t position);

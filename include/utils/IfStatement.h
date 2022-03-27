#pragma once

#include "utils/Conditional.h"
#include "utils/WritableContent.h"
#include <sstream>

struct IfStatement : public Conditional
{
	IfStatement(Instruction condition, WritableContent body, WritableContent elseBody = {}) : 
		Conditional("if", std::move(condition), std::move(body)),
		m_elseBody(elseBody)
	{ }

	~IfStatement() { }

	WritableContent m_elseBody;
};

template<>
void write(const IfStatement &ifStatement, std::stringstream &out, std::size_t position);

#pragma once

#include "utils/core/Writer.h"
#include "utils/Instruction.h"
#include "utils/WritableContent.h"

struct Function
{
	Function(Instruction templateData, Instruction signature, WritableContent body);
	~Function();

	Instruction m_template;
	Instruction m_signature;
	WritableContent m_body;
};

template<>
void write(const Function &function, std::stringstream &out, std::size_t position);

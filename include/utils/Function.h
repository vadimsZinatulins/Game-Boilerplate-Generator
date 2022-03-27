#pragma once

#include "utils/core/Writer.h"
#include "utils/Instruction.h"
#include "utils/WritableContent.h"

#include "utils/StringTrim.h"

#include <sstream>
#include <type_traits>

struct Class;

struct Function
{
	struct Definition { const Function &function;	};
	struct Declaration { const Function &function; };

	Function(Instruction preModifier, Instruction returnType, Instruction name, Instruction postModifier, WritableContent body);
	~Function();

	Definition defenition() const; 
	Declaration declaration() const;

	void setParentName(std::string name);

	Instruction m_preModifier;
	Instruction m_returnType;
	Instruction m_name;
	Instruction m_postModifier;
	WritableContent m_body;

	std::string m_parentName;
};

template<>
void write(const Function::Definition &definition, std::stringstream &out, std::size_t position);

template<>
void write(const Function::Declaration &declaration, std::stringstream &out, std::size_t position);

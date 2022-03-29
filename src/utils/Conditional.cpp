#include "utils/Conditional.h"

Conditional::Conditional(Instruction signature, Instruction condition, WritableContent body) :
	m_condition(signature + "(" + condition + ")"),
	m_body(std::move(body))
{ }

Conditional::~Conditional() { }


template<>
void write(const Conditional &conditional, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << conditional.m_condition << "\n";
	out << std::string(position, '\t') << "{\n";
	write(conditional.m_body, out, position + 1);
	out << std::string(position, '\t') << "}\n";
}


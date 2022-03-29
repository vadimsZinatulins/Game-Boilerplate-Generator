#include "utils/SwitchStatement.h"
#include <string>

SwitchStatement::SwitchStatement(Instruction condition, WritableContent body) : 
	Conditional("switch", std::move(condition), std::move(body))
{ }

SwitchStatement::~SwitchStatement() { }

template<>
void write(const SwitchStatement &switchStatement, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << switchStatement.m_condition << '\n';
	out << std::string(position, '\t') << "{\n";
	write(switchStatement.m_body, out, position);
	out << std::string(position, '\t') << "}";
}

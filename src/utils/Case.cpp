#include "utils/Case.h"

#include <string>

Case::Case(Instruction condition, WritableContent body) :
	m_condition(std::move(condition)),
	m_body(std::move(body))
{

}

Case::~Case()
{

}

template<>
void write(const Case &caseStatement, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << "case " + caseStatement.m_condition + ":\n";
	write(caseStatement.m_body, out, position + 1);
	out << std::string(position + 1, '\t') << "break;";
}

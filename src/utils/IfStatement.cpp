#include "utils/IfStatement.h"
#include "utils/WritableContent.h"

IfStatement::IfStatement(Instruction condition, WritableContent body, WritableContent elseBody) : 
	Conditional("if", std::move(condition), std::move(body)),
	m_elseBody(elseBody)
{ }

IfStatement::~IfStatement() { }

template<>
void write(const IfStatement &ifStatement, std::stringstream &out, std::size_t position)
{
	write((Conditional&)(ifStatement), out, position);
	if(ifStatement.m_elseBody.size())
	{
		out << std::string(position, '\t') << "else\n";
		out << std::string(position, '\t') << "{\n";
		write(ifStatement.m_elseBody, out, position + 1);
		out << std::string(position, '\t') << "}\n";
	}
}

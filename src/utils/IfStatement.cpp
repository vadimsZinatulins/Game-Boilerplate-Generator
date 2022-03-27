#include "utils/IfStatement.h"
#include "utils/WritableContent.h"

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

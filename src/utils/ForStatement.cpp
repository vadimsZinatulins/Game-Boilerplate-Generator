#include "utils/ForStatement.h"

ForStatement::ForStatement(Instruction initialization, Instruction condition, Instruction increment, WritableContent body) : 
	Conditional("for", initialization + "; " + condition + "; " + increment, std::move(body))
{ }

ForStatement::ForStatement(Instruction condition, WritableContent body) : 
	Conditional("for", std::move(condition), std::move(body))
{ }

ForStatement::~ForStatement() { }

	template<>
void write(const ForStatement &forStatement, std::stringstream &out, std::size_t position) {
	write((Conditional&)(forStatement), out, position);
}

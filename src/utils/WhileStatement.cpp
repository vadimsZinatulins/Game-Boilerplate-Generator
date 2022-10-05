#include "utils/WhileStatement.h"
#include "utils/Conditional.h"

WhileStatement::WhileStatement(Instruction condition, WritableContent body) : 
	Conditional("while", std::move(condition), std::move(body))
{ }

WhileStatement::~WhileStatement() { }

template<>
void write(const WhileStatement &whileStatement, std::stringstream &out, std::size_t position) {
	write((Conditional&)(whileStatement), out, position);
}

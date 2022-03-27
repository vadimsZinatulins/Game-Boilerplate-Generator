#include "utils/WhileStatement.h"
#include "utils/Conditional.h"

template<>
void write(const WhileStatement &whileStatement, std::stringstream &out, std::size_t position)
{
	write((Conditional&)(whileStatement), out, position);
}

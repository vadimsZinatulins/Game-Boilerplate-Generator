#include "utils/ForStatement.h"

template<>
void write(const ForStatement &forStatement, std::stringstream &out, std::size_t position)
{
	write((Conditional&)(forStatement), out, position);
}

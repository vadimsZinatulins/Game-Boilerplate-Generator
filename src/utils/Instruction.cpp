#include "utils/Instruction.h"

template<>
void write(const Instruction &instruction, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << instruction << std::endl;
}

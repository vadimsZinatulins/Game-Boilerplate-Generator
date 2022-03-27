#include "utils/WritableContent.h"

template<>
void write(const WritableContent &doc, std::stringstream &out, std::size_t position)
{
	for(const auto &param : doc) write(param, out, position);
}


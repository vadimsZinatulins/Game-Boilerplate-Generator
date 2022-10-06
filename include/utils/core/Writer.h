#pragma once

#include <sstream>

template<typename T>
void write(const T &parameter, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << parameter << '\n';
}


#pragma once

#include "utils/core/Writer.h"
#include "utils/WritableContent.h"

#include <string>

struct Namespace
{
	Namespace(std::string name, WritableContent content);
	~Namespace();

	std::string m_name;
	WritableContent m_content;
};

template<>
void write(const Namespace &ns, std::stringstream &out, std::size_t position);

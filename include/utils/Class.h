#pragma once

#include "utils/core/Writer.h"
#include "utils/WritableContent.h"

#include <sstream>
#include <string>

struct Class
{
	Class(std::string name, WritableContent publicContent, WritableContent protectedContent, WritableContent m_privateContent);
	~Class();

	std::string m_name;

	WritableContent m_publicContent;
	WritableContent m_protectedContent;
	WritableContent m_privateContent;
};

template<>
void write(const Class &param, std::stringstream &out, std::size_t position);


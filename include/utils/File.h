#pragma once

#include "utils/WritableContent.h"

#include <cstddef>
#include <sstream>
#include <string>

struct File
{
	File(std::string path, WritableContent includes, WritableContent content);
	~File();

	void write() const;

	std::string m_path;
	WritableContent m_includes;
	WritableContent m_content;
};


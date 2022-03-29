#pragma once

#include <cstddef>
#include <sstream>
#include <string>

class ProjectClass
{
public:
	ProjectClass(std::string projectName);
	~ProjectClass();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_projectName;
};

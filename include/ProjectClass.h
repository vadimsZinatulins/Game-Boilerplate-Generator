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
	friend void write(const ProjectClass &project, std::stringstream &out, std::size_t position);

	void generateHeader() const;
	void generateSource() const;

	std::string m_projectName;
};

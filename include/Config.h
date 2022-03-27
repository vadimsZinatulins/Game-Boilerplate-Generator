#pragma once

#include <string>

class Config
{
public:
	Config() = default;
	~Config() = default;

	void setProjectName(std::string name);

	void createFile() const;
private:
	std::string m_projectName { "" };
};

#pragma once

#include <string>
class MainFile
{
public:
	MainFile(std::string projectName);
	~MainFile();

	void generate() const;
private:
	void generateSource() const;

	std::string m_projectName;
};

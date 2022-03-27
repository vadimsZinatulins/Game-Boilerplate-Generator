#pragma once

#include <string>
#include <vector>

class CMakeFile
{
public:
	CMakeFile() = default;
	~CMakeFile() = default;

	void setVersion(std::size_t major, std::size_t minor);
	void addFileToCompile(std::string newFile);
	void setProjectName(std::string name);

	void createFile() const;
private:
	std::size_t m_majorVersion { 1 };
	std::size_t m_minorVersion { 0 };

	std::string m_name { "" };
	std::vector<std::string> m_filesToCompile { };
};

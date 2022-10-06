#pragma once

#include <string>
#include <vector>

namespace gbg::generators {

class ProjectListFiles {
public:
	ProjectListFiles() = default;
	~ProjectListFiles() = default;

	void setProjectName(std::string name);
	void setWithSDL2ImageExtra(bool flag);
	void setProjectVersion(std::size_t major, std::size_t minor = 0, std::size_t patch = 0, std::size_t tweak = 0);
	void addFileToCompile(std::string newFile);

	void generateFiles() const;
private:
	void generateBaseListFile() const;
	void generateSrcListFile() const;

	std::string generateProjectVersion() const;
	std::string generateSourceFiles() const;
	std::string generateFindLibraries() const;
	std::string generateLinkLibraries() const;

	std::size_t m_projectMajorVersion { 1 };
	std::size_t m_projectMinorVersion { 0 };
	std::size_t m_projectPatchVersion { 0 };
	std::size_t m_projectTweakVersion { 0 };

	std::string m_name { "" };
	std::vector<std::string> m_filesToCompile { };
	bool m_withSDL2ImageExtra { false };
};

}

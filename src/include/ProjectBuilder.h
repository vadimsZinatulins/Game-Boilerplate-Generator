#pragma once

#include <string>

namespace gbg {

class ProjectBuilder {
public:
	ProjectBuilder() = default;
	~ProjectBuilder() = default;

	void setProjectName(std::string projectName);

	void setWithSDL2ImageExtra(bool flag);
	void setWithLogsExtra(bool flag);

	void build();
private:
	std::string m_projectName { "" };

	bool m_withSDL2ImageExtra { false };
	bool m_withLogsExtra { true };
};

}


#pragma once

#include <string>

namespace gbg {

class ProjectBuilder {
public:
	ProjectBuilder() = default;
	~ProjectBuilder() = default;

	void setProjectName(std::string projectName);

	void setWithVulkanExtra(bool flag);
	void setWithLogsExtra(bool flag);

	void build();
private:
	std::string m_projectName { "" };

	bool m_withVulkanExtra { false };
	bool m_withSDL2ImageExtra { false };
	bool m_withLogsExtra { true };
};

}


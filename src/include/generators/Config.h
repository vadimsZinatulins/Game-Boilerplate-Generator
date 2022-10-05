#pragma once

#include <string>

namespace gbg::generators {

class Config
{
public:
	Config() = default;
	~Config() = default;

	void setProjectName(std::string name);
	void setWithSDL2ImageExtra(bool flag);

	void createFile() const;
private:
	std::string generateExtras() const;

	std::string m_projectName { "" };
	bool m_withSDL2ImageExtra { false };
};

}


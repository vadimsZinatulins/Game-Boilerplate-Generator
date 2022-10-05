#pragma once

#include <string>

namespace gbg::generators {

class ProjectClass {
public:
	ProjectClass(std::string projectName);
	~ProjectClass();

	void generate() const;
private:
	void generateHeader() const;
	void generateSource() const;

	std::string m_projectName;
};

}

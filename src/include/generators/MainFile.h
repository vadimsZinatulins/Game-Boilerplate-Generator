#pragma once

#include <string>

namespace gbg::generators {

class MainFile {
public:
	MainFile(std::string projectName);
	~MainFile();

	void generate() const;
private:
	void generateSource() const;

	std::string m_projectName;
};

}

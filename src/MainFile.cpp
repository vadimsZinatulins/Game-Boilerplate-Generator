#include "MainFile.h"
#include "utils/File.h"
#include "utils/Function.h"


MainFile::MainFile(std::string projectName) : m_projectName(projectName) { }
MainFile::~MainFile() { }

void MainFile::generate() const
{
	generateSource();
}

void MainFile::generateSource() const
{
	File("src/main.cpp", { "#include \"" + m_projectName + ".h\"" }, {
		Function("", "int main(int argc, char *argv[])", { 
			m_projectName + "().run();",
			"return 0;"
		})
	}).write();
}


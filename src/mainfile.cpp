#include "mainfile.h"
#include "utils.h"

void generateMain(const std::string &projectName)
{
	mkfile("src/main.cpp", {
		"#include \"" + projectName + ".h\"",
		"",
		"int main(int argc, char *argv[])",
		"{",
		"	" + projectName + "().run();",
		"	return 0;",
		"}"
	});
}

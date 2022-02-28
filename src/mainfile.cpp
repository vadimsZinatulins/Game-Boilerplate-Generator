#include "mainfile.h"

#include <fstream>

void generateMain(const std::string &projectName)
{
	std::ofstream src("src/main.cpp");

	src << "#include \"" << projectName << ".h\"\n\n";
	src << "int main(int argc, char *argv[])\n{\n";
	src << "\t" << projectName << "().run();\n";
	src << "\treturn 0;\n";
	src << "}\n";

	src.close();
}

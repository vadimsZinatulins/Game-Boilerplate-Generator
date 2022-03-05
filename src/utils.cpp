#include "utils.h"

#include <fstream>

void mkfile(std::string fileName, std::vector<std::string> content)
{
	std::ofstream file(fileName);

	for(const auto &line : content) file << line << '\n';

	file.close();
}

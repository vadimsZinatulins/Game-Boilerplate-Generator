#include "utils/File.h"
#include "utils/core/Writer.h"
#include "utils/WritableContent.h"

#include <fstream>
#include <sstream>

File::File(std::string path, WritableContent includes, WritableContent content) :
	m_path(std::move(path)),
	m_includes(std::move(includes)),
	m_content(std::move(content)) { }

File::~File() { }

void File::write() const {
	std::ofstream file(m_path);

	std::stringstream fileContent;

	::write(m_includes, fileContent, 0);
	fileContent << '\n';
	::write(m_content, fileContent, 0);

	file << fileContent.str();

	file.close();
}

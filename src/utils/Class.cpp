#include "utils/Class.h"

Class::Class(std::string name, WritableContent publicContent, WritableContent protectedContent, WritableContent m_privateContent) :
	m_name(name),
	m_publicContent(std::move(publicContent)),
	m_protectedContent(std::move(protectedContent)),
	m_privateContent(std::move(m_privateContent))
{ }

Class::~Class() { }

template<>
void write(const Class &param, std::stringstream &out, std::size_t position) {
	out << std::string(position, '\t') << "class " << param.m_name << " {\n";
	if(param.m_publicContent.size()) {
		out << std::string(position, '\t') << "public:\n";
		::write(param.m_publicContent, out, position + 1);
	}

	if(param.m_protectedContent.size())	{
		out << std::string(position, '\t') << "protected:\n";
		::write(param.m_protectedContent, out, position + 1);
	}

	if(param.m_privateContent.size()) {
		out << std::string(position, '\t') << "private:\n";
		::write(param.m_privateContent, out, position + 1);
	}
	out << std::string(position, '\t') << "};\n";
}

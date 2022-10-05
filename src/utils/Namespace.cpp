#include "utils/Namespace.h"
#include "utils/WritableContent.h"
#include <cstddef>
#include <sstream>
#include <string>

Namespace::Namespace(std::string name, WritableContent content) :
	m_name(std::move(name)),
	m_content(std::move(content)) { }
Namespace::~Namespace() { }

template<>
void write(const Namespace &ns, std::stringstream &out, std::size_t position) {
	out << std::string(position, '\t') << "namespace " << ns.m_name << " {\n\n";
	write(ns.m_content, out, position);
	out << std::string(position, '\t') << "\n}\n";
}


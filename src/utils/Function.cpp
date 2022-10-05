#include "utils/Function.h"
#include <string>

Function::Function(Instruction templateData, Instruction signature, WritableContent body) :
	m_template(std::move(templateData)),
	m_signature(std::move(signature)),
	m_body(std::move(body)) { }

Function::~Function() { }

template<>
void write(const Function &function, std::stringstream &out, std::size_t position) {
	if(function.m_template.size()) out << std::string(position, '\t') << function.m_template << '\n';
	out << std::string(position, '\t') << function.m_signature << " {\n";
	::write(function.m_body, out, position + 1);
	out << std::string(position, '\t') << "}\n";
}


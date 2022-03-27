#include "utils/Function.h"
#include "utils/Class.h"

Function::Function(Instruction preModifier, Instruction returnType, Instruction name, Instruction postModifier, WritableContent body) :
		m_preModifier(std::move(preModifier)),
		m_returnType(std::move(returnType)),
		m_name(std::move(name)),
		m_postModifier(std::move(postModifier)),
		m_body(std::move(body)),
		m_parentName("")
{

}

Function::~Function() { }

Function::Definition Function::defenition() const
{ 
	return { *this }; 
}

Function::Declaration Function::declaration() const
{ 
	return { *this }; 
}

void Function::setParentName(std::string name)
{
	m_parentName = std::move(name);
}

template<>
void write(const Function::Definition &definition, std::stringstream &out, std::size_t position)
{
	const auto &func = definition.function;

	std::string def = func.m_preModifier + " " + func.m_returnType + " " + func.m_name + " " + func.m_postModifier;
	trim(def);

	out << std::string(position, '\t') << def << ";\n";
}

template<>
void write(const Function::Declaration &declaration, std::stringstream &out, std::size_t position)
{
	const auto &func = declaration.function;

	std::string def = func.m_returnType + " " + func.m_parentName + func.m_name;
	trim(def);

	out << std::string(position, '\t') << def << '\n';
	out << std::string(position, '\t') << "{\n";
	write(func.m_body, out, position + 1);
	out << std::string(position, '\t') << "}\n";
}

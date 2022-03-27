#include "utils/Class.h"
#include "utils/Instruction.h"
#include "utils/WritableContent.h"
#include "utils/core/Writer.h"
#include "utils/Function.h"

#include <iostream>
#include <string>

void writeDefinition(std::size_t index, const Class::Definition &definition, std::stringstream &out, std::size_t position)
{
	if(definition.m_classes[index].size())
	{
		for(const auto &content : definition.m_classes[index]) write(content.definition(), out, position + 1);
		out << std::string(position, '\t') << "\n";
	}


	if(definition.m_methods[index].size())
	{
		for(const auto &content : definition.m_methods[index]) write(content.defenition(), out, position + 1);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : definition.m_attributes[index]) write(content, out, position + 1);
}

Class::Class(std::string name) : m_name(name) { }
Class::~Class() { }

void Class::addMethod(Function function, Modifiers modifier)
{
	function.setParentName(getFullName() + "::");
	m_methods[static_cast<std::size_t>(modifier)].push_back(function);
}

void Class::addAttribute(Instruction attribute, Modifiers modifier)
{
	m_attributes[static_cast<std::size_t>(modifier)].push_back(attribute);
}

void Class::addClass(Class childClass, Modifiers modifier)
{
	childClass.setParentName(getFullName() + "::");

	m_classes[static_cast<std::size_t>(modifier)].push_back(childClass);
}

void Class::setParentName(std::string name)
{
	m_parentName = name;
	std::string fullName = getFullName() + "::";

	for(auto &method : m_methods[0]) method.setParentName(fullName);
	for(auto &method : m_methods[1]) method.setParentName(fullName);
	for(auto &method : m_methods[2]) method.setParentName(fullName);

	for(auto &childClass : m_classes[0]) childClass.setParentName(fullName);
	for(auto &childClass : m_classes[1]) childClass.setParentName(fullName);
	for(auto &childClass : m_classes[2]) childClass.setParentName(fullName);
}

std::string Class::getFullName() const
{
	return m_parentName + m_name;
}

Class::Definition Class::definition() const
{
	return { m_name, m_methods, m_attributes, m_classes };
}

Class::Declaration Class::declaration() const
{
	return { m_name, m_methods, m_classes };
}

template<>
void write(const Class::Definition &definition, std::stringstream &out, std::size_t position)
{
	out << std::string(position, '\t') << "class " << definition.m_name << "\n";
	out << std::string(position, '\t') << "{\n";

	if(definition.m_methods[0].size() || definition.m_attributes[0].size() || definition.m_classes[0].size()) 
	{
		out << std::string(position, '\t') << "public:\n";
		writeDefinition(0, definition, out, position);
	}

	if(definition.m_methods[1].size() || definition.m_attributes[1].size() || definition.m_classes[1].size()) 
	{
		out << std::string(position, '\t') << "protected:\n";
		writeDefinition(1, definition, out, position);
	}

	if(definition.m_methods[2].size() || definition.m_attributes[2].size() || definition.m_classes[2].size()) 
	{
		out << std::string(position, '\t') << "private:\n";
		writeDefinition(2, definition, out, position);
	}

	out << std::string(position, '\t') << "};\n";
}

template<>
void write(const Class::Declaration &declaration, std::stringstream &out, std::size_t position)
{
	for(const auto &content : declaration.m_methods[0])
	{
		write(content.declaration(), out, position);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : declaration.m_methods[1])
	{
		write(content.declaration(), out, position);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : declaration.m_methods[2])
	{
		write(content.declaration(), out, position);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : declaration.m_classes[0])
	{
		write(content.declaration(), out, position);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : declaration.m_classes[1])
	{
		write(content.declaration(), out, position);
		out << std::string(position, '\t') << "\n";
	}

	for(const auto &content : declaration.m_classes[2]) write(content.declaration(), out, position);
}

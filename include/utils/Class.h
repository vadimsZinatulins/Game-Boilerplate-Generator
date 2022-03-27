#pragma once

#include "utils/WritableContent.h"
#include "utils/core/Writer.h"
#include "utils/Function.h"
#include "utils/Instruction.h"

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

struct Class
{
	enum class Modifiers { Public = 0, Protected = 1, Private = 2 };

	struct Definition
	{
		const std::string &m_name;
		const std::vector<Function> *m_methods;
		const std::vector<Instruction> *m_attributes;
		const std::vector<Class> *m_classes;
		const WritableContent *m_extras;
	};

	struct Declaration
	{
		const std::string &m_name;
		const std::vector<Function> *m_methods;
		const std::vector<Class> *m_classes;
	};

	Class(std::string name);
	~Class();

	void addMethod(Function function, Modifiers modifier);
	void addAttribute(Instruction attribute, Modifiers modifier);
	void addClass(Class childClass, Modifiers modifier);

	void setParentName(std::string name);
	std::string getFullName() const;

	Definition definition() const;
	Declaration declaration() const;

	std::string m_name;

	std::vector<Function> m_methods[3];
	std::vector<Instruction> m_attributes[3];
	std::vector<Class> m_classes[3];

	std::string m_parentName;
};

template<>
void write(const Class::Definition &definition, std::stringstream &out, std::size_t position);

template<>
void write(const Class::Declaration &declaration, std::stringstream &out, std::size_t position);

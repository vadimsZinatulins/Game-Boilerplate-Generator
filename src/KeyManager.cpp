#include "KeyManager.h"
#include "utils/ForStatement.h"
#include "utils/IfStatement.h"
#include "utils/Instruction.h"
#include "utils/Function.h"
#include "utils/Namespace.h"
#include "utils/File.h"

#include <ctime>
#include <fstream>

KeyManager::KeyManager()
{
	m_class.addAttribute("KeyManager() = default;", Class::Modifiers::Private);
	m_class.addAttribute("~KeyManager() = default;\n", Class::Modifiers::Private);

	m_class.addAttribute("KeyMap m_currFrameKeys;", Class::Modifiers::Private);
	m_class.addAttribute("KeyMap m_oldFrameKeys;\n", Class::Modifiers::Private);

	m_class.addAttribute("template<typename T>", Class::Modifiers::Private);
	m_class.addAttribute("friend class Game;", Class::Modifiers::Private);


	{
		Function getInstance("static", "KeyManager&", "getInstance()", "", {
			"static KeyManager instance;",
			"return instance;"
		});

		m_class.addMethod(getInstance, Class::Modifiers::Public);
	}

	{
		Function isKeyPressed("", "bool", "isKeyPressed(Key key) const", "", {
			"return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key);"
		});

		m_class.addMethod(isKeyPressed, Class::Modifiers::Public);
	}

	{
		Function isKeyDown("", "bool", "isKeyDown(Key key) const", "", {
			"return m_currFrameKeys.contains(key);"
		});

		m_class.addMethod(isKeyDown, Class::Modifiers::Public);
	}

	{
		Function isKeyReleased("", "bool", "isKeyReleased(Key key) const", "", {
			"return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key);"
		});

		m_class.addMethod(isKeyReleased, Class::Modifiers::Public);
	}

	{
		Function update("", "void", "update()", "", { "m_oldFrameKeys = m_currFrameKeys;" });

		m_class.addMethod(update, Class::Modifiers::Private);
	}

	{
		Function keyPressed("", "void", "keyPressed(Key key)", "", { "m_currFrameKeys.insert(key);" });

		m_class.addMethod(keyPressed, Class::Modifiers::Private);
	}

	{
		Function keyReleased("", "void", "keyReleased(Key key)", "", { "m_currFrameKeys.remove(key);" });

		m_class.addMethod(keyReleased, Class::Modifiers::Private);
	}

	{
		Class kmc("KeyMap");
		
		kmc.addAttribute("static constexpr int CacheLineSize { 64 };", Class::Modifiers::Public);
		kmc.addAttribute("static constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };", Class::Modifiers::Public);

		kmc.addAttribute("Key m_keys[ArraySize];", Class::Modifiers::Private);
		kmc.addAttribute("unsigned char m_size { 0 };", Class::Modifiers::Private);

		{
			Function operatorEqual("", "void", "operator=(const KeyMap &other)", "", {
				"m_size = other.m_size;",
				ForStatement("unsigned char i = 0", "i < m_size", "++i", { "m_keys[i] = other.m_keys[i];" })
			});

			kmc.addMethod(operatorEqual, Class::Modifiers::Public);
		}

		{
			Function insert("", "void", "insert(Key key)", "", {
				IfStatement("!contains(key) && m_size < KeyManager::KeyMap::ArraySize", { "m_keys[m_size++] = key;" })
			});

			kmc.addMethod(insert, Class::Modifiers::Public);
		}

		{
			Function contains("", "bool", "contains(Key key) const", "", {
				ForStatement("unsigned char i = 0", "i < m_size", "++i", {
					IfStatement("m_keys[i] == key", { "return true;" })
				}),
				"return false;"
			});

			kmc.addMethod(contains, Class::Modifiers::Public);
		}

		{
			Function remove("", "void", "remove(Key key)", "", {
				ForStatement("unsigned char i = 0", "i < m_size", "++i", {
					IfStatement("m_keys[i] == key", {
						"m_keys[i] = m_keys[--m_size];",
						"return;"
					})
				}),
			});
			kmc.addMethod(remove, Class::Modifiers::Public);
		}

		m_class.addClass(kmc, Class::Modifiers::Private);
	}
}

KeyManager::~KeyManager()
{

}

void KeyManager::generate() const
{
	generateHeader();
	generateSource();
}

void KeyManager::generateHeader() const
{
	Namespace ns("BE", { 
		"using Key = unsigned int;",
		"",
		m_class.definition() 
	});

	File("include/BE/KeyManager.h", { "#pragma once\n" }, { ns }).write();
}

void KeyManager::generateSource() const
{
	Namespace ns("BE", { m_class.declaration() });

	File("src/BE/KeyManager.cpp", { "#include \"BE/KeyManager.h\"\n" }, { ns }).write();
}


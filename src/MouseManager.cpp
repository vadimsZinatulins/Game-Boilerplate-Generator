#include "MouseManager.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"
#include "utils/Instruction.h"
#include "utils/Namespace.h"

MouseManager::MouseManager()
{
	m_class.addAttribute("MouseManager() = default;", Class::Modifiers::Private);
	m_class.addAttribute("~MouseManager() = default;\n", Class::Modifiers::Private);

	m_class.addAttribute("int m_scroll { 0 };\n", Class::Modifiers::Private);

	m_class.addAttribute("int m_x { 0 };", Class::Modifiers::Private);
	m_class.addAttribute("int m_y { 0 };\n", Class::Modifiers::Private);

	m_class.addAttribute("int m_dx { 0 };", Class::Modifiers::Private);
	m_class.addAttribute("int m_dy { 0 };\n", Class::Modifiers::Private);

	m_class.addAttribute("char m_buttonState { 0 };\n", Class::Modifiers::Private);

	m_class.addAttribute("template<typename T>", Class::Modifiers::Private);
	m_class.addAttribute("friend class Game;", Class::Modifiers::Private);

	{
		Function getInstance("static", "MouseManager&", "getInstance()", "", {
			"static MouseManager instance;",
			"return instance;"
		});

		m_class.addMethod(getInstance, Class::Modifiers::Public);
	}

	{
		Function isButtonPressed("", "bool", "isButtonPressed(MouseButton btn) const", "", {
			"char btnMask = (1 << (static_cast<char>(btn) - 1));",
			"return !((btnMask << 4) & m_buttonState) && (btnMask & m_buttonState);"
		});

		m_class.addMethod(isButtonPressed, Class::Modifiers::Public);
	}

	{
		Function isButtonDown("", "bool", "isButtonDown(MouseButton btn) const", "", {
			"char btnMask = (1 << (static_cast<char>(btn) - 1));",
			"return (btnMask & m_buttonState);"
		});

		m_class.addMethod(isButtonDown, Class::Modifiers::Public);
	}

	{
		Function isButtonReleased("", "bool", "isButtonReleased(MouseButton btn) const", "", {
			"char btnMask = (1 << (static_cast<char>(btn) - 1));",
			"return ((btnMask << 4) & m_buttonState) && !(btnMask & m_buttonState);"
		});

		m_class.addMethod(isButtonReleased, Class::Modifiers::Public);
	}

	{
		Function update("", "void", "update()", "", {
			"char currFrameMask = m_buttonState & 0x0f;",
			"m_buttonState = (currFrameMask << 4) | currFrameMask;",
			"m_dx = m_dy = 0;"
		});

		m_class.addMethod(update, Class::Modifiers::Private);
	}

	{
		Function buttonPressed("", "void", "buttonPressed(MouseButton btn)", "", {
			"m_buttonState = (1 << (static_cast<char>(btn) - 1)) | m_buttonState;"
		});

		m_class.addMethod(buttonPressed, Class::Modifiers::Private);
	}

	{
		Function buttonReleased("", "void", "buttonReleased(MouseButton btn)", "", {
			"m_buttonState = ((1 << (static_cast<char>(btn) - 1)) ^ 0xff) & m_buttonState;"
		});

		m_class.addMethod(buttonReleased, Class::Modifiers::Private);
	}

	{
		Function mouseMoved("", "void", "mouseMoved(int x, int y, int dx, int dy)", "", {
			"m_x = x;",
			"m_y = y;",
			"m_dx = dx;",
			"m_dy = dy;"
		});

		m_class.addMethod(mouseMoved, Class::Modifiers::Private);
	}
}

MouseManager::~MouseManager()
{

}

void MouseManager::generate() const
{
	generateHeader();
	generateSource();
}

void MouseManager::generateHeader() const
{
	Namespace ns("BE", { "enum class MouseButton:char { Left = 1, Middle = 2, Right = 3 };\n", m_class.definition() });

	File("include/BE/MouseManager.h", { "#pragma once\n" }, { ns }).write();
}

void MouseManager::generateSource() const
{
	Namespace ns("BE", { m_class.declaration() });

	File("src/BE/MouseManager.cpp", { "#include \"BE/MouseManager.h\"" }, { ns }).write();
}
	

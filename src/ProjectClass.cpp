#include "ProjectClass.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"

namespace gbg::generators {


ProjectClass::ProjectClass(std::string projectName) : m_projectName(std::move(projectName)) { }
ProjectClass::~ProjectClass() { }

void ProjectClass::generate() const  {
	generateHeader();
	generateSource();
}

void ProjectClass::generateHeader() const {
	File("include/" + m_projectName + ".h", {
		"#pragma once",
		"",
		"#include \"be/Game.h\""
	}, {
		Class(m_projectName + " final : public be::Game<" + m_projectName + ">", {
			m_projectName + "() = default;",
			"~" + m_projectName + "() = default;"
		}, {}, {
			"friend class be::Game<" + m_projectName + ">;",
			"",
			"void initialize();",
			"void shutdown();"
		})
	}).write();
}

void ProjectClass::generateSource() const {
	File("src/" + m_projectName + ".cpp", {
		"#include \"" + m_projectName + ".h\"",
		"#include \"MainMenuScene.h\"",
		"#include \"be/SceneManager.h\"",
		"",
		"#include <SDL.h>"
	}, {
		Function("", "void " + m_projectName + "::initialize()", { "be::SceneManager::getInstance().pushScene<MainMenuScene>();" }),
		Function("", "void " + m_projectName + "::shutdown()", { "" })
	}).write();
}

}

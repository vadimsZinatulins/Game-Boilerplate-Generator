#include "ProjectClass.h"
#include "utils/Class.h"
#include "utils/File.h"
#include "utils/Function.h"

ProjectClass::ProjectClass(std::string projectName) : m_projectName(std::move(projectName)) { }
ProjectClass::~ProjectClass() { }

void ProjectClass::generate() const 
{
	generateHeader();
	generateSource();
}

void ProjectClass::generateHeader() const
{
	File("include/" + m_projectName + ".h", {
		"#pragma once",
		"",
		"#include \"BE/Game.h\""
	}, {
		Class(m_projectName + " final : public BE::Game<Test>", {
			m_projectName + "() = default;",
			"~" + m_projectName + "() = default;"
		}, {}, {
			"friend class BE::Game<" + m_projectName + ">;",
			"",
			"void initialize();",
			"void shutdown();"
		})
	}).write();
}

void ProjectClass::generateSource() const
{
	File("src/" + m_projectName + ".cpp", {
		"#include \"" + m_projectName + ".h\"",
		"#include \"MainMenuScene.h\"",
		"#include \"BE/SceneManager.h\"",
		"",
		"#include <SDL2/SDL.h>"
	}, {
		Function("", "void Test::initialize()", { "BE::SceneManager::getInstance().pushScene<MainMenuScene>();" }),
		Function("", "void Test::shutdown()", { "" })
	}).write();
}

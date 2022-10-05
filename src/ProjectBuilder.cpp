#include "ProjectBuilder.h"
#include "workspace.h"
#include "ProjectListFiles.h"
#include "KeyManager.h"
#include "Logger.h"

#include "Config.h"
#include "MouseManager.h"
#include "Time.h"
#include "Cronometer.h"
#include "Random.h"
#include "SceneManager.h"
#include "Game.h"
#include "ProjectClass.h"
#include "MainFile.h"
#include "TextureManager.h"

#include <SimpleTaskManager/make_task.h>
#include <iostream>

namespace gbg {

void ProjectBuilder::setProjectName(std::string projectName) {
	m_projectName = projectName;
}

void ProjectBuilder::setWithSDL2ImageExtra(bool flag) {
	m_withSDL2ImageExtra = flag;
}

void ProjectBuilder::setWithLogsExtra(bool flag) {
	m_withLogsExtra = flag;
}

void ProjectBuilder::build() {
	if(m_projectName.empty()) {
		return;
	}

	auto generateWorkspaceTask { stm::make_task([&] { 
		Log() << "Generating workspace\n";

		generators::generateWorkspace(m_projectName); 
	}) };

	auto generateCMakeFileTask { stm::make_task([&] {
		Log() << "Generating listfiles\n";

		generators::ProjectListFiles listFiles;

		listFiles.setProjectName(m_projectName);
		listFiles.setProjectVersion(1);
		listFiles.setWithSDL2ImageExtra(m_withSDL2ImageExtra);

		listFiles.addFileToCompile("be/KeyManager");
		listFiles.addFileToCompile("be/MouseManager");
		listFiles.addFileToCompile("be/Time");
		listFiles.addFileToCompile("be/Cronometer");
		listFiles.addFileToCompile("be/Random");
		listFiles.addFileToCompile("be/SceneManager");
		if(m_withSDL2ImageExtra) {
			listFiles.addFileToCompile("be/TextureManager");
		}
		listFiles.addFileToCompile("MainMenuScene");
		listFiles.addFileToCompile(m_projectName);
		listFiles.addFileToCompile("main");

		listFiles.generateFiles();
	}, generateWorkspaceTask) };

	auto generateConfigTask { stm::make_task([&] {
		Log() << "Generating src/config/config.h.in file\n";

		generators::Config config;
		config.setProjectName(m_projectName);
		config.setWithSDL2ImageExtra(m_withSDL2ImageExtra);

		config.createFile();
	}, generateWorkspaceTask) };

	auto generateKeyManagerTask { stm::make_task([] {
		Log() << "Generating KeyManager Class\n";

		generators::KeyManager().generate();	
	}, generateWorkspaceTask) };
	
	auto generateMouseManagerTask { stm::make_task([] {
		Log() << "Generating MouseManager Class\n";

		generators::MouseManager().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateTimeClassTask { stm::make_task([] {
		Log() << "Generating Time Class\n";

		generators::Time().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateCronometerTask { stm::make_task([] {
		Log() << "Generating Cronometer Class\n";

		generators::Cronometer().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateRandomTask { stm::make_task([] {
		Log() << "Generating Random Class\n";

		gbg::generators::Random().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateSceneManagerTask { stm::make_task([] {
		Log() << "Generating SceneManager Class\n";

		gbg::generators::SceneManager().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateTextureManagerTask { stm::make_task([&] {
		if(m_withSDL2ImageExtra) {
			Log() << "Generating TextureManager file\n";

			gbg::generators::TextureManager().generate(); 
		}
	}, generateWorkspaceTask) };
	
	auto generateGameTask { stm::make_task([&] {
		Log() << "Generating Game Class\n";

		gbg::generators::Game game;
		
		game.setWithSDL2ImageExtra(m_withSDL2ImageExtra);
		game.generate(); 
	}, generateWorkspaceTask) };
	
	auto generateProjectNameFileTask { stm::make_task([&] {
		Log() << "Generating " + m_projectName + " Class\n";

		gbg::generators::ProjectClass(m_projectName).generate(); 
	}, generateWorkspaceTask) };
	
	auto generateMainFileTask { stm::make_task([&] {
		Log() << "Generating main file\n";

		gbg::generators::MainFile(m_projectName).generate(); 
	}, generateWorkspaceTask) };
	

	generateCMakeFileTask->result();
	generateConfigTask->result();
	generateKeyManagerTask->result();
	generateMouseManagerTask->result();
	generateTimeClassTask->result();
	generateCronometerTask->result();
	generateRandomTask->result();
	generateSceneManagerTask->result();
	generateTextureManagerTask->result();
	generateGameTask->result();
	generateProjectNameFileTask->result();
	generateMainFileTask->result();

	if(m_withLogsExtra) {
		Log() << "\n\tcd " << m_projectName << " && cmake -B build/ && ln -s build/compile_commands.json . && cmake --build build/\n";
	}
}

}

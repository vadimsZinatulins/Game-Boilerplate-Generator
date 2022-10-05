#include "ProjectBuilder.h"
#include "workspace.h"
#include "ProjectListFiles.h"
#include "config.h"
#include "Task.h"
#include "Logger.h"
#include "Config.h"
#include "KeyManager.h"
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
	auto generateWorkspaceTask { stm::make_task([&] { 
		Log() << "Generating workspace\n";

		generators::generateWorkspace(m_projectName); 
	}) };

	auto generateCMakeFileTask { stm::make_task([&] {
		Log() << "Generating listfiles\n";

		generators::ProjectListFiles listFiles;

		listFiles.setProjectName(m_projectName);
		listFiles.setProjectVersion(1);
		listFiles.addFileToCompile("be/KeyManager");
		listFiles.addFileToCompile("be/MouseManager");
		listFiles.addFileToCompile("be/Time");
		listFiles.addFileToCompile("be/Cronometer");
		listFiles.addFileToCompile("be/Random");
		listFiles.addFileToCompile("be/SceneManager");
		listFiles.addFileToCompile("be/TextureManager");
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
 		KeyManager().generate();	
	}, generateWorkspaceTask) };
	
	auto generateMouseManagerTask { stm::make_task([] {
		Log() << "Generating MouseManager Class\n";

 		MouseManager().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateTimeClassTask { stm::make_task([] {
		Log() << "Generating Time Class\n";

 		Time().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateCronometerTask { stm::make_task([] {
		Log() << "Generating Cronometer Class\n";

 		Cronometer().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateRandomTask { stm::make_task([] {
		Log() << "Generating Random Class\n";

 		Random().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateSceneManagerTask { stm::make_task([] {
		Log() << "Generating SceneManager Class\n";

 		SceneManager().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateTextureManagerTask { stm::make_task([] {
		Log() << "Generating TextureManager file\n";

 		TextureManager().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateGameTask { stm::make_task([] {
		Log() << "Generating Game Class\n";

 		Game().generate(); 
	}, generateWorkspaceTask) };
	
	auto generateProjectNameFileTask { stm::make_task([&] {
		Log() << "Generating " + m_projectName + " Class\n";

 		ProjectClass(m_projectName).generate(); 
	}, generateWorkspaceTask) };
	
	auto generateMainFileTask { stm::make_task([&] {
		Log() << "Generating main file\n";

 		MainFile(m_projectName).generate(); 
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
		Log() << "cd " << m_projectName << " && cmake -E chdir build/ cmake .. && ln -s build/compile_commands.json . && cmake --build build/";
	}
}

}

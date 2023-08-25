#include "ProjectBuilder.h"
#include "workspace.h"
#include "ProjectListFiles.h"
#include "KeyManager.h"
#include "Logger.h"

#include "MouseManager.h"
#include "Time.h"
#include "Cronometer.h"
#include "Random.h"
#include "SceneManager.h"
#include "Game.h"
#include "ProjectClass.h"
#include "MainFile.h"
#include "TextureManager.h"

#include "utils/replaceAll.h"

#include "tempaltes/ConfigTemplate.h"
#include "tempaltes/ListFilesTemplate.h"

#include <SimpleTaskManager/make_task.h>
#include <iostream>
#include <fstream>
#include <sstream>

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
	const auto projectName { m_projectName };
	const auto withSDL2ImageExtra { m_withSDL2ImageExtra };

	if(projectName.empty()) {
		return;
	}

	auto generateWorkspaceTask { stm::make_task([&] { 
		Log() << "Generating workspace\n";

		generators::generateWorkspace(projectName); 
	}) };

	auto generateCMakeFileTask { stm::make_task([&] {
		Log() << "Generating listfiles\n";

		auto withSdl2ImageExtra { m_withSDL2ImageExtra };
		
		{
			std::stringstream sdl2ImageLibContent;

			if(withSdl2ImageExtra) {
				sdl2ImageLibContent << ROOT_LISTFILE_SDL2_IMAGE_FETCH_CONTENT_TEMPLATE;
			}

			ReplaceContent rc = {
				{ "{SDL2_IMAGE_FETCH_CONTENT}", sdl2ImageLibContent.str() },
				{ "{NAME}", projectName }
			};

			std::ofstream rootListfile("CMakeLists.txt");
			rootListfile << replaceAll(ROOT_LISTFILE_TEMPLATE, rc);
			rootListfile.close();
		}

		{
			std::stringstream sdl2ImageContent;
			std::stringstream sdl2ImageSourceContent;
			if(withSdl2ImageExtra) {
				sdl2ImageContent << SRC_LISTFILE_SDL2_IMAGE_LIBRARY_TEMPLATE;
				sdl2ImageSourceContent <<  SRC_LISTFILE_SDL2_IMAGE_CPPS_TEMPLATE;
			}

			ReplaceContent rc = {
				{ "{SDL2_IMAGE_CONTENT}", sdl2ImageContent.str() },
				{ "{SDL2_IMAGE_SOURCES}", sdl2ImageSourceContent.str() },
				{ "{NAME}", projectName }
			};

			std::ofstream srcListfile("src/CMakeLists.txt");
			srcListfile << replaceAll(SRC_LISTFILE_TEMPLATE, rc);
			srcListfile.close();
		}
	}, generateWorkspaceTask) };

	auto generateConfigTask { stm::make_task([&] {
		Log() << "Generating src/config/config.h.in file\n";

		std::stringstream sdl2ImageContent;

		if(withSDL2ImageExtra) {
			sdl2ImageContent << CONFIG_H_IN_SDL2_IMAGE_CONTENT_TEMPLATE;
		}

		std::ofstream configHInFile("config/config.h.in");
		configHInFile << replaceAll(CONFIG_H_IN_TEMPLATE, { { "{SDL_IMAGE_CONTENT}", sdl2ImageContent.str() } });
		configHInFile.close();
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
		if(withSDL2ImageExtra) {
			Log() << "Generating TextureManager file\n";

			gbg::generators::TextureManager().generate(); 
		}
	}, generateWorkspaceTask) };
	
	auto generateGameTask { stm::make_task([&] {
		Log() << "Generating Game Class\n";

		gbg::generators::Game game;
		
		game.setWithSDL2ImageExtra(withSDL2ImageExtra);
		game.generate(); 
	}, generateWorkspaceTask) };
	
	auto generateProjectNameFileTask { stm::make_task([&] {
		Log() << "Generating " + projectName + " Class\n";

		gbg::generators::ProjectClass(projectName).generate(); 
	}, generateWorkspaceTask) };
	
	auto generateMainFileTask { stm::make_task([&] {
		Log() << "Generating main file\n";

		gbg::generators::MainFile(projectName).generate(); 
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
		Log() << "\n\tcd " << projectName << " && cmake -B build/ && ln -s build/compile_commands.json . && cmake --build build/\n";
	}
}

}

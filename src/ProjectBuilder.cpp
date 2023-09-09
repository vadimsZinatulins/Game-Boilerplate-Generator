#include "ProjectBuilder.h"
#include "workspace.h"
#include "Logger.h"

#include "utils/replaceAll.h"

#include "templates/ProjectClassTemplate.h"
#include "templates/CronometerTemplate.h"
#include "templates/ConfigTemplate.h"
#include "templates/ListFilesTemplate.h"
#include "templates/TimeTemplate.h"
#include "templates/KeyManagerTemplate.h"
#include "templates/MouseManagerTemplate.h"
#include "templates/RandomTemplate.h"
#include "templates/ISceneTemplate.h"
#include "templates/MainSceneTemplate.h"
#include "templates/SceneManagerTemplate.h"
#include "templates/TextureManagerTemplate.h"
#include "templates/MainTemplate.h"
#include "templates/GameTemplate.h"

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

		{
			std::stringstream sdl2ImageLibContent;

			if(withSDL2ImageExtra) {
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
			if(withSDL2ImageExtra) {
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
		Log() << "Generating config.h.in file\n";

		std::stringstream sdl2ImageContent;

		if(withSDL2ImageExtra) {
			sdl2ImageContent << CONFIG_H_IN_SDL2_IMAGE_CONTENT_TEMPLATE;
		}

		ReplaceContent rc =  { 
			{ "{SDL_IMAGE_CONTENT}", sdl2ImageContent.str() }, 
			{ "{NAME}", projectName } 
		};

		std::ofstream configHInFile("config/config.h.in");
		configHInFile << replaceAll(CONFIG_H_IN_TEMPLATE, rc);
		configHInFile.close();
	}, generateWorkspaceTask) };

	auto generateKeyManagerTask { stm::make_task([] {
		Log() << "Generating KeyManager Class\n";

		{
			std::ofstream keyManagerHFile("include/be/KeyManager.h");
			keyManagerHFile << KEYMANAGER_H_TEMPLATE;
			keyManagerHFile.close();
		}
		
		{
			std::ofstream keyManagerCppFile("src/be/KeyManager.cpp");
			keyManagerCppFile << KEYMANAGER_CPP_TEMPLATE;
			keyManagerCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateMouseManagerTask { stm::make_task([] {
		Log() << "Generating MouseManager Class\n";

		{
			std::ofstream mouseManagerHFile("include/be/MouseManager.h");
			mouseManagerHFile << MOUSEMANAGER_H_TEMPLATE;
			mouseManagerHFile.close();
		}
		
		{
			std::ofstream mouseManagerCppFile("src/be/MouseManager.cpp");
			mouseManagerCppFile << MOUSEMANAGER_CPP_TEMPLATE;
			mouseManagerCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateTimeClassTask { stm::make_task([] {
		Log() << "Generating Time Class\n";

		{
			std::ofstream timerHFile("include/be/Time.h");
			timerHFile << TIMER_H_TEMPLATE;
			timerHFile.close();
		}

		{
			std::ofstream timerCppFile("src/be/Time.cpp");
			timerCppFile << TIMER_CPP_TEMPLATE;
			timerCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateCronometerTask { stm::make_task([] {
		Log() << "Generating Cronometer Class\n";

		{
			std::ofstream cronometerHFile("include/be/Cronometer.h");
			cronometerHFile << CRONOMETER_H_TEMPLATE;
			cronometerHFile.close();
		}

		{
			std::ofstream cronometerCppFile("src/be/Cronometer.cpp");
			cronometerCppFile << CRONOMETER_CPP_TEMPLATE;
			cronometerCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateRandomTask { stm::make_task([] {
		Log() << "Generating Random Class\n";

		{
			std::ofstream randomHFile("include/be/Random.h");
			randomHFile << RANDOM_H_TEMPLATE;
			randomHFile.close();
		}

		{
			std::ofstream randomCppFile("src/be/Random.cpp");
			randomCppFile << RANDOM_CPP_TEMPLATE;
			randomCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateISceneTask { stm::make_task([]{
		Log() << "Generating IScene Class\n";

		std::ofstream isceneHFile("include/be/IScene.h");
		isceneHFile << ISCENE_H_TEMPLATE;
		isceneHFile.close();

	}, generateWorkspaceTask) };

	auto generateMainSceneTask { stm::make_task([]{
		Log() << "Generating MainScene Class\n";

		{
			std::ofstream mainSceneHFile("include/MainScene.h");
			mainSceneHFile << MAINSCENE_H_TEMPLATE;
			mainSceneHFile.close();
		}

		{
			std::ofstream mainSceneCppFile("src/MainScene.cpp");
			mainSceneCppFile << MAINSCENE_CPP_TEMPLATE;
			mainSceneCppFile.close();
		}

	}, generateWorkspaceTask) };

	auto generateSceneManagerTask { stm::make_task([] {
		Log() << "Generating SceneManager Class\n";

		{
			std::ofstream sceneManagerHFile("include/be/SceneManager.h");
			sceneManagerHFile << SCENEMANAGER_H_TEMPLATE;
			sceneManagerHFile.close();
		}
		
		{
			std::ofstream sceneManagerCppFile("src/be/SceneManager.cpp");
			sceneManagerCppFile << SCENEMANAGER_CPP_TEMPLATE;
			sceneManagerCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateTextureManagerTask { stm::make_task([&] {
		if(withSDL2ImageExtra) {
			Log() << "Generating TextureManager Class\n";

			{
				std::ofstream textureManagerHFile("include/be/TextureManager.h");
				textureManagerHFile << TEXTUREMANAGER_H_TEMPLATE;
				textureManagerHFile.close();
			}
			
			{
				std::ofstream textureManagerCppFile("src/be/TextureManager.cpp");
				textureManagerCppFile << TEXTUREMANAGER_CPP_TEMPLATE;
				textureManagerCppFile.close();
			}
		}
	}, generateWorkspaceTask) };
	
	auto generateGameTask { stm::make_task([&] {
		Log() << "Generating Game Class\n";

		std::stringstream textureManagerIncludeContent;
		std::stringstream sdlImageIncludeContent;
		std::stringstream imgInitContent;
		std::stringstream textureManagerInitContent;
		std::stringstream textureManagerClearContent;
		std::stringstream imgQuitContent;

		if(withSDL2ImageExtra) {
			textureManagerIncludeContent << GAME_TEXTURE_MANAGER_INCLUDE_TEMPLATE;
			sdlImageIncludeContent << GAME_SDL_IMAGE_INCLUDE_TEMPLATE;
			imgInitContent << GAME_IMG_INIT_TEMPLATE;
			textureManagerInitContent << GAME_TEXTURE_MANAGER_INIT_TEMPLATE;
			textureManagerClearContent << GAME_TEXTURE_MANAGER_CLEAR_TEMPLATE;
			imgQuitContent << GAME_IMG_QUIT_TEMPLATE;
		}

		ReplaceContent rc = {
			{ "{TEXTURE_MANAGER_INCLUDE}", textureManagerIncludeContent.str() },
			{ "{SDL_IMAGE_INCLUDE}", sdlImageIncludeContent.str() },
			{ "{IMG_INIT}", imgInitContent.str() },
			{ "{TEXTURE_MANAGER_INIT}", textureManagerInitContent.str() },
			{ "{TEXTURE_MANAGER_CLEAR}", textureManagerClearContent.str() },
			{ "{IMG_QUIT}", imgQuitContent.str() }
		};

		std::ofstream GameHFile("include/be/Game.h");
		GameHFile << replaceAll(GAME_H_TEMPLATE, rc);
		GameHFile.close();
	}, generateWorkspaceTask) };
	
	auto generateProjectNameFileTask { stm::make_task([&] {
		Log() << "Generating " + projectName + " Class\n";

		{
			std::ofstream projectClassHFile("include/" + projectName + ".h");
			projectClassHFile << replaceAll(PROJECTCLASS_H_TEMPLATE, { { "{NAME}", projectName } });
			projectClassHFile.close();
		}

		{
			std::ofstream projectClassCppFile("src/" + projectName + ".cpp");
			projectClassCppFile << replaceAll(PROJECTCLASS_CPP_TEMPLATE, { { "{NAME}", projectName } });
			projectClassCppFile.close();
		}
	}, generateWorkspaceTask) };
	
	auto generateMainFileTask { stm::make_task([&] {
		Log() << "Generating main.cpp file\n";

		std::ofstream mainCppFile("src/main.cpp");
		mainCppFile << replaceAll(MAIN_CPP_TEMPLATE, { { "{NAME}", projectName } });
		mainCppFile.close();
	}, generateWorkspaceTask) };
	

	generateCMakeFileTask->result();
	generateConfigTask->result();
	generateKeyManagerTask->result();
	generateMouseManagerTask->result();
	generateTimeClassTask->result();
	generateCronometerTask->result();
	generateRandomTask->result();
	generateISceneTask->result();
	generateMainSceneTask->result();
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

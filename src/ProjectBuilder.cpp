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
#include "templates/MainTemplate.h"
#include "templates/GameTemplate.h"

#include "math/MathExtensionBuilder.h"

#include <SimpleTaskManager/make_task.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace gbg {

void ProjectBuilder::setProjectName(std::string projectName) {
	m_projectName = projectName;
}

void ProjectBuilder::setWithMathExtra(bool flag) {
	m_withMathExtra = flag;
}

void ProjectBuilder::setWithSdlImageExtra(bool flag) {
	m_withSdlImageExtra = flag;
}

void ProjectBuilder::setWithLogsExtra(bool flag) {
	m_withLogsExtra = flag;
}

void ProjectBuilder::build() {
	const auto projectName { m_projectName };
	const auto withMathExtra { m_withMathExtra };
	const auto withSdlImageExtra { m_withSdlImageExtra };

	if(projectName.empty()) {
		return;
	}

	auto generateWorkspaceTask { stm::make_task([&] { 
		Log() << "Generating workspace\n";

		generators::generateWorkspace(projectName, withMathExtra); 
	}) };

	auto generateCMakeFileTask { stm::make_task([&] {
		Log() << "Generating listfiles\n";

		{
			std::ofstream rootListfile("CMakeLists.txt");
			std::stringstream sdl3ImageLibContent;

			if(withSdlImageExtra) {
				sdl3ImageLibContent << ROOT_LISTFILE_SDL3_IMAGE_FETCH_CONTENT_TEMPLATE;
			}

			ReplaceContent rc = {
				{ "{SDL3_IMAGE_FETCH_CONTENT}", sdl3ImageLibContent.str() },
				{ "{NAME}", projectName }
			};

			rootListfile << replaceAll(ROOT_LISTFILE_TEMPLATE, rc);
			rootListfile.close();
		}

		{
			std::ofstream srcListfile("src/CMakeLists.txt");
			std::vector<std::string> libraries = {
				"SDL3::SDL3-static"
			};

			if(withSdlImageExtra) {
				libraries.push_back("SDL3_image::SDL3_image");
			}

			std::stringstream librariesContent;
			for(const auto &lib : libraries) {
				librariesContent << "\t\t" << lib << "\n";
			}

			std::stringstream mathFilesContent;

			if(withMathExtra) {
				mathFilesContent << "\n\n# Math extension files\n";
				mathFilesContent << "\t\tbe/math/Vec2.cpp\n";
				mathFilesContent << "\t\tbe/math/Vec3.cpp\n";
				mathFilesContent << "\t\tbe/math/Vec4.cpp\n";
				mathFilesContent << "\t\tbe/math/Mat2.cpp\n";
				mathFilesContent << "\t\tbe/math/Mat3.cpp";
			}

			ReplaceContent rc = {
				{ "{NAME}", projectName },
				{ "{MATH_FILES}", mathFilesContent.str() },
				{ "{LIBRARIES}", librariesContent.str() }
			};

			srcListfile << replaceAll(SRC_LISTFILE_TEMPLATE, rc);
			srcListfile.close();
		}
	}, generateWorkspaceTask) };

	auto generateConfigTask { stm::make_task([&] {
		Log() << "Generating config.h.in file\n";

		ReplaceContent rc =  { 
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
	
	auto generateGameTask { stm::make_task([&] {
		Log() << "Generating Game Class\n";
		
		std::ofstream GameHFile("include/be/Game.h");
		GameHFile << GAME_H_TEMPLATE;
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
	generateGameTask->result();
	generateProjectNameFileTask->result();
	generateMainFileTask->result();

	if(withMathExtra) {
		buildMathExtension(generateWorkspaceTask, projectName);
	}

	if(m_withLogsExtra) {
		Log() << "\n\tcd " << projectName << " && cmake -B build/ && ln -s build/compile_commands.json . && cmake --build build/\n";
	}
}

}

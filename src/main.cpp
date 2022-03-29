#include "config.h"
#include "workspace.h"
// #include "cmakelists.h"
// #include "keymanager.h"
// #include "mousemanager.h"
// #include "timeclass.h"
// #include "cronometerclass.h"
// #include "game.h"
// #include "projectnameclass.h"
// #include "mainfile.h"
// #include "configfile.h"
// #include "randomclass.h"
#include "Task.h"
#include "Logger.h"
// #include "scenemanager.h"
// #include "mainmenuscene.h"

#include "CMakeFile.h"
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

#include <string>

int main(int argc, char *argv[])
{
	Log() << "Running gbgen version: " + std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION) + "\n\n";

	if(argc != 2)
	{
		Log() << "Wrong argument count\n";
		Log() << "Usage: gbgen [PROJECT_NAME]\n";

		return 1;
	}

	std::string projectName(argv[1]);

	execute({ MakeTask("Generating workspace", [&]{ generateWorkspace(projectName); }) });

	execute({
		MakeTask("Generating CMakeLists.txt", [&]{
			CMakeFile cmakefile;
			cmakefile.setProjectName(projectName);
			cmakefile.setVersion(1, 0);
			cmakefile.addFileToCompile("BE/KeyManager");
			cmakefile.addFileToCompile("BE/MouseManager");
			cmakefile.addFileToCompile("BE/Time");
			cmakefile.addFileToCompile("BE/Cronometer");
			cmakefile.addFileToCompile("BE/Random");
			cmakefile.addFileToCompile("BE/SceneManager");
			cmakefile.addFileToCompile("MainMenuScene");
			cmakefile.addFileToCompile(projectName);
			cmakefile.addFileToCompile("main");

			cmakefile.createFile();
		}),
		MakeTask("Generating config/config.h.in file", [&]{ 
			Config config;
			config.setProjectName(projectName);

			config.createFile();
		}),
		MakeTask("Generating KeyManager Class", []{ KeyManager().generate();	}),
		MakeTask("Generating MouseManager Class", []{ MouseManager().generate(); }),
		MakeTask("Generating Time Class", []{ Time().generate(); }),
		MakeTask("Generating Cronometer Class", []{ Cronometer().generate(); }),
		MakeTask("Generating Random Class", []{ Random().generate(); }),
		MakeTask("Generating SceneManager Class", []{ SceneManager().generate(); }),
		MakeTask("Generating Game Class", []{ Game().generate(); }),
		MakeTask("Generating " + projectName + " Class", [&]{ ProjectClass(projectName).generate(); }),
		MakeTask("Generating main file", [&]{ MainFile(projectName).generate(); })
	});

	Log() << "\nDone! You can now run the following commands:\n";
	Log() << "\tcd " + projectName + '\n';
	Log() << "\tcmake -E chdir build/ cmake ..\n";
	Log() << "\tln -s build/compile_commands.json .\n";
	Log() << "\tcmake --build build/\n";
	Log() << "\tbin/" << projectName + "\n\n";
	Log() << "Complete command:\n";
	Log() << "\tcd " << projectName << " && cmake -E chdir build/ cmake .. && ln -s build/compile_commands.json . && cmake --build build/\n\n";
	Log() << "And change the both config/config.h.in and CMakeLists.txt files as you want. Have fun!\n\n";

	return 0;
}

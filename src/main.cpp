#include "config.h"
#include "workspace.h"
#include "Task.h"
#include "Logger.h"
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
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(&argv[0], &argv[0 + argc]);

	if(args.size() < 2)
	{
		Log() << "Wrong argument count\n";
		Log() << "Usage: gbgen [--build-output|-bo] <PROJECT_NAME>\n";

		return 1;
	}

	std::size_t nameIndex = 1;
	bool printArg = true;

	if(args[1] == "--build-output" || args[1] == "-bo")
	{
		nameIndex = 2;
		printArg = false;
	}
	else Log() << "Running gbgen version: " + std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION) + "\n\n";

	std::string projectName(std::move(args[nameIndex]));

	execute(printArg, { MakeTask("Generating workspace", [&]{ generateWorkspace(projectName); }) });

	execute(printArg, {
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

	if(printArg) 
	{
		Log() << "\nDone! You can now run the following commands:\n";
		Log() << "\tcd " + projectName + '\n';
		Log() << "\tcmake -E chdir build/ cmake ..\n";
		Log() << "\tln -s build/compile_commands.json .\n";
		Log() << "\tcmake --build build/\n";
		Log() << "\tbin/" << projectName + "\n\n";
		Log() << "Complete command:\n";
		Log() << "\tcd " << projectName << " && cmake -E chdir build/ cmake .. && ln -s build/compile_commands.json . && cmake --build build/\n\n";
		Log() << "And change the both config/config.h.in and CMakeLists.txt files as you want. Have fun!\n\n";
	}
	else Log() << "cd " << projectName << " && cmake -E chdir build/ cmake .. && ln -s build/compile_commands.json . && cmake --build build/";

	return 0;
}

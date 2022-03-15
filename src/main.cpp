#include "config.h"
#include "workspace.h"
#include "cmakelists.h"
#include "keymanager.h"
#include "mousemanager.h"
#include "timeclass.h"
#include "cronometerclass.h"
#include "game.h"
#include "projectnameclass.h"
#include "mainfile.h"
#include "configfile.h"
#include "randomclass.h"
#include "Task.h"
#include "Logger.h"
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

	std::vector<Task> tasks = {
		MakeTask("Generating workspace", [&]{ generateWorkspace(projectName); }),
		MakeTask("Generating CMakeLists.txt", [&]{ generateCMakeLists(projectName, { "main", "BE/KeyManager", "BE/MouseManager", "BE/Time", "BE/Cronometer", "BE/Random", projectName }); }),
		MakeTask("Generating KeyManager class", []{ generateKeyManager(); }),
		MakeTask("Generating MouseManager class", []{ generateMouseManager(); }),
		MakeTask("Generating Game class", []{ generateGameClass(); }),
		MakeTask("Generating Time class", []{ generateTimeClass(); }),
		MakeTask("Generating Cronometer class", []{ generateCronometerClass(); }),
		MakeTask("Generating Random class", []{ generateRandomClass(); }),
		MakeTask("Generating " + projectName + " class", [&]{ generateProjectNameClass(projectName); }),
		MakeTask("Generating src/main.cpp", [&]{ generateMain(projectName); }),
		MakeTask("Generating config/config.h.in", [&]{ generateConfigFile(projectName); })
	};

	execute(tasks);

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

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

#include <iostream>
#include <functional>
#include <utility>
#include <vector>

using Task = std::pair<std::string, std::function<void()>>;
constexpr auto MakeTask = std::make_pair<std::string, std::function<void()>>;

void execute(std::vector<Task> &tasks)
{
	for(std::size_t i = 0; i < tasks.size(); ++i)
	{
		std::cout << "[" << (i + 1) << "/" << tasks.size() << "] " << tasks[i].first << std::endl;
		tasks[i].second();
	}
}

int main(int argc, char *argv[])
{
	std::cout << "Running gbgen version: " << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
	if(argc != 2)
	{
		std::cout << "Wrong argument count" << std::endl;
		std::cout << "Usage: gbgen [PROJECT_NAME]" << std::endl;

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

	std::cout << "Done! You can now run the following commands:" << std::endl;
	std::cout << "\tcd " << projectName << std::endl;
	std::cout << "\tcmake -E chdir build/ cmake .." << std::endl;
	std::cout << "\tln -s build/compile_commands.json ." << std::endl;
	std::cout << "\tcmake --build build/" << std::endl;
	std::cout << "\tbin/" << projectName << std::endl << std::endl;
	std::cout << "Complete command:" << std::endl;
	std::cout << "\tcd " << projectName << " && cmake -E chdir build/ cmake .. && ln -s build/compile_commands.json . && cmake --build build/" << std::endl << std::endl;
	std::cout << "And change the both config/config.h.in and CMakeLists.txt files as you want. Have fun!" << std::endl;

	return 0;
}

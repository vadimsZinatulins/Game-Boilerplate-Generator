#include "utils/ArgsParser.h"
#include "ProjectBuilder.h"
#include "Logger.h"

#include <SimpleTaskManager/Scheduler.h>
#include <iostream>

using namespace gbg;

int main(int argc, char *argv[]) {
	gbg::ProjectBuilder builder;

	gbg::utils::ArgsParser parser;

	parser
		.arg("--name")
		.aliases({ "-n" })
		.description("Set the project name")
		.valueAction([&builder] (std::string projectName) { builder.setProjectName(projectName); })
		.required()
		.build();

	parser
		.arg("--help")
		.aliases({ "-h" })
		.description("Display help")
		.action([&parser]{ std::cout << parser.getHelpText() << std::endl; })
		.earlyExit()
		.build();

	parser
		.arg("--with-sdl-image")
		.description("Enable SDL_image extra")
		.action([&builder]{ builder.setWithSdlImageExtra(true); })
		.build();

	parser
		.arg("--with-math")
		.description("Enable math extra")
		.action([&builder]{ builder.setWithMathExtra(true); })
		.build();

	parser
		.arg("--verbose")
		.aliases({ "-v" })
		.description("Enable verbose logging")
		.action([]{ gbg::Logger::getInstance().setVerbose(true); })
		.build();

	try {
		// If no early exit after parsing, build the project
		if (parser.parse(argc, argv)) {
			stm::Scheduler::getInstance().initialize();
			builder.build();
			stm::Scheduler::getInstance().terminate();
		}
	} catch(const std::runtime_error& e) {
		Log().log("Error: " + std::string(e.what()), LogType::Error);
		return 1;
	}

	return 0;
}

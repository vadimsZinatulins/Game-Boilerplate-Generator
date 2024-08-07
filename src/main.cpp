#include "utils/ArgsParser.h"
#include "writeHelp.h"
#include "ProjectBuilder.h"

#include <SimpleTaskManager/Scheduler.h>

int main(int argc, char *argv[])
{
	gbg::utils::ArgsParser parser(argc, argv);

	gbg::ProjectBuilder builder;

	parser.addAction({ "--name", "-n" }, [&builder] (std::string projectName) { builder.setProjectName(projectName); });
	parser.addAction({ "--help", "-h" }, []{ gbg::utils::writeHelp(); });
	parser.addAction({ "--with-vulkan" }, [&builder]{ builder.setWithVulkanExtra(true); });
	parser.addAction({ "--no-logs" }, [&builder]{ builder.setWithLogsExtra(false); });

	parser.parse();

	stm::Scheduler::getInstance().initialize();
	builder.build();
	stm::Scheduler::getInstance().terminate();

	return 0;
}

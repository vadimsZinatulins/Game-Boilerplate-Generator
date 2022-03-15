#include "Task.h"
#include "Logger.h"

#include <iostream>

void execute(std::vector<Task> &tasks)
{
	for(std::size_t i = 0; i < tasks.size(); ++i)
	{
		Log() << "[" << (i + 1) << "/" << tasks.size() << "] " << tasks[i].first << '\n';

		tasks[i].second();
	}
}

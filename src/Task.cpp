#include "Task.h"
#include "Logger.h"

#include <string>
#include <thread>

void execute(std::vector<Task> &tasks)
{
	std::thread threads[tasks.size()];

	for(std::size_t i = 0; i < tasks.size(); ++i)
		threads[i] = std::move(std::thread([i, &tasks] () {
			Log() << tasks[i].first + '\n';
			tasks[i].second();
		}));

	for(std::size_t i = 0; i < tasks.size(); ++i) threads[i].join();
}

#pragma once

#include <functional>
#include <vector>

using Task = std::pair<std::string, std::function<void()>>;
constexpr auto MakeTask = std::make_pair<std::string, std::function<void()>>;

void execute(std::vector<Task> &tasks);


#pragma once

#include <functional>
#include <vector>
#include <string>

using Task = std::pair<std::string, std::function<void()>>;
constexpr auto MakeTask = std::make_pair<std::string, std::function<void()>>;

void execute(bool print, const std::vector<Task> &&tasks);


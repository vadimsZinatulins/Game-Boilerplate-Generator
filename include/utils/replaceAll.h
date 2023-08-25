#pragma once

#include <vector>
#include <utility>
#include <string>

using ReplaceContent = std::vector<std::pair<std::string, std::string>>;

std::string replaceAll(const std::string &subject, const ReplaceContent &replaceContent);
#pragma once

#include "WritableUnit.h"

#include <vector>

using WritableContent = std::vector<WritableUnit>;

template<>
void write(const WritableContent &doc, std::stringstream &out, std::size_t position);

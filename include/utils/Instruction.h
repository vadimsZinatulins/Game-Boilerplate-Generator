#pragma once

#include "core/Writer.h"

#include <string>

using Instruction = std::string;

template<>
void write(const Instruction &instruction, std::stringstream &out, std::size_t position);

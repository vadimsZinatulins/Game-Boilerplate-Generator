#pragma once

const auto VULKAN_MAIN_CPP_TEMPLATE { R"(#include "{NAME}.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
	try {
		{NAME}().run();
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
)" };
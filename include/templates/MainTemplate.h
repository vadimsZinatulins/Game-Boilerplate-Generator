#pragma once

auto MAIN_CPP_TEMPLATE { R"(#include "{NAME}.h"

int main(int argc, char *argv[]) {
	{NAME}().run();
	return 0;
}
)" };
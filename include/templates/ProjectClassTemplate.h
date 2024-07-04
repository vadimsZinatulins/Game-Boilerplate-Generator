#pragma once

const auto PROJECTCLASS_H_TEMPLATE { R"(#pragma once

#include "be/Game.h"

class {NAME} final : public be::Game<{NAME}> {
public:
	{NAME}() = default;
	~{NAME}() = default;
private:
	friend class be::Game<{NAME}>;
	
	void initialize();
	void shutdown();
};
)" };

const auto PROJECTCLASS_CPP_TEMPLATE { R"(#include "{NAME}.h"
#include "MainScene.h"
#include "be/SceneManager.h"

#include <SDL3/SDL.h>

void {NAME}::initialize() {
	be::SceneManager::getInstance().pushScene<MainScene>();
}

void {NAME}::shutdown() {
	
}
)" };
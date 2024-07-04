#pragma once

auto MAINSCENE_H_TEMPLATE { R"(#pragma once

#include "be/IScene.h"

class MainScene : public be::IScene {
public:
	void initialize() override;
	void shutdown() override;
	
	void update() override;
	void render(SDL_Renderer *renderer) override;
};
)" };

auto MAINSCENE_CPP_TEMPLATE { R"(#include "MainScene.h"

#include <SDL3/SDL.h>

void MainScene::initialize() {
	
}

void MainScene::shutdown() {
	
}

void MainScene::update() {
	
}

void MainScene::render(SDL_Renderer *renderer) {
	
}
)" };
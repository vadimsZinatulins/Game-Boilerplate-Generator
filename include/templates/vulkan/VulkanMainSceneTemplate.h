#pragma once

auto VULKAN_MAINSCENE_H_TEMPLATE { R"(#pragma once

#include "be/IScene.h"

class MainScene : public be::IScene {
public:
	void initialize() override;
	void shutdown() override;
	
	void update() override;
	void render() override;
};
)" };

auto VULKAN_MAINSCENE_CPP_TEMPLATE { R"(#include "MainScene.h"

void MainScene::initialize() {
	
}

void MainScene::shutdown() {
	
}

void MainScene::update() {
	
}

void MainScene::render() {
	
}
)" };
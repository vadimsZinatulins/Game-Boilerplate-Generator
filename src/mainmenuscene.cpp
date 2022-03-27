#include "mainmenuscene.h"
#include "utils.h"

void generateMainMenuSceneHeader()
{
	mkfile("include/MainMenuScene.h", {
		"#pragma once",
		"",
		"#include \"BE/IScene.h\"",
		"",
		"class MainMenuScene : public BE::IScene",
		"{",
		"public:",
		"	void initialize() override;",
		"	void shutdown() override;",
		"",
		"	void update() override;",
		"	void render(SDL_Renderer *renderer) override;",
		"};",
		"",
	});
}

void generateMainMenuSceneSource()
{
	mkfile("src/MainMenuScene.cpp", {
		"#include \"MainMenuScene.h\"",
		"",
		"#include <SDL2/SDL.h>",
		"",
		"void MainMenuScene::initialize()",
		"{",
		"",
		"}",
		"",
		"void MainMenuScene::shutdown()",
		"{",
		"",
		"}",
		"",
		"void MainMenuScene::update()",
		"{",
		"",
		"}",
		"",
		"void MainMenuScene::render(SDL_Renderer *renderer)",
		"{",
		"",
		"}",
	});
}

void generateMainMenuScene()
{
	generateMainMenuSceneHeader();
	generateMainMenuSceneSource();
}

#include "game.h"

#include <fstream>

void generateGameHeader()
{
	std::ofstream header("include/Game.h");

	header << "#pragma once\n\n";
	header << "struct SDL_Window;\n";
	header << "struct SDL_Renderer;\n\n";
	header << "class Game \n{\n";
	header << "public:\n";
	header << "\tGame() = default;\n";
	header << "\tvirtual ~Game() = default;\n\n";
	header << "\t void run();\n\n";
	header << "protected:\n";
	header << "\tvirtual void initialize() = 0;\n";
	header << "\tvirtual void shutdown() = 0;\n";
	header << "\tvirtual void update() = 0;\n";
	header << "\tvirtual void render(SDL_Renderer *renderer) = 0;\n";
	header << "private:\n";
	header << "\tvoid init();\n";
	header << "\tvoid loop();\n";
	header << "\tvoid close();\n\n";
	header << "\tSDL_Window *m_window { nullptr };\n";
	header << "\tSDL_Renderer *m_renderer { nullptr };\n";
	header << "};\n";

	header.close();
}

void generateGameSource()
{
	std::ofstream src("src/Game.cpp");

	// Add inclues
	src << "#include \"Game.h\"\n";
	src << "#include \"Time.h\"\n";
	src << "#include \"KeyManager.h\"\n";
	src << "#include \"config.h\"\n\n";
	src << "#include <SDL2/SDL.h>\n\n";

	// Add "run" method
	src << "void Game::run()\n{\n";
	src << "\tinit();\n";
	src << "\tloop();\n";
	src << "\tclose();\n";
	src << "}\n\n";

	// Add "init" method
	src << "void Game::init()\n{\n";
	src << "\tSDL_Init(SDL_INIT_VIDEO);\n\n";
	src << "\tm_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);\n";
	src << "\tm_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);\n\n";
	src << "\tSDL_SetRenderDrawColor(m_renderer, 0x00f, 0x00f, 0x00f, 0xff);\n\n";
	src << "\tinitialize();\n";
	src << "}\n\n";
	
	// Add "loop" method
	src << "void Game::loop()\n{\n";
	src << "\tauto &keys = KeyManager::getInstance();\n";
	src << "\tbool isRunning = true;\n";
	src << "\tSDL_Event e;\n\n";
	src << "\tUint32 startFrame = SDL_GetTicks();\n";
	src << "\tUint32 startPreviousFrame = SDL_GetTicks();\n\n";
	src << "\twhile(isRunning)\n\t{\n";
	src << "\t\tTime frameTimer;\n\n";
	src << "\t\tkeys.update();\n\n";
	src << "\t\twhile(SDL_PollEvent(&e))\n\t\t{\n";
	src << "\t\t\tswitch(e.type)\n\t\t\t{\n";
	src << "\t\t\tcase SDL_QUIT:\n";
	src << "\t\t\t\tisRunning = false;\n";
	src << "\t\t\t\tbreak;\n";
	src << "\t\t\tcase SDL_KEYDOWN:\n";
	src << "\t\t\t\tkeys.keyPressed(e.key.keysym.sym);\n";
	src << "\t\t\t\tbreak;\n";
	src << "\t\t\tcase SDL_KEYUP:\n";
	src << "\t\t\t\tkeys.keyReleased(e.key.keysym.sym);\n";
	src << "\t\t\t\tbreak;\n";
	src << "\t\t\t}\n";
	src << "\t\t}\n\n";
	src << "\t\tupdate();\n\n";
	src << "\t\tSDL_RenderClear(m_renderer);\n";
	src << "\t\trender(m_renderer);\n";
	src << "\t\tSDL_RenderPresent(m_renderer);\n\n";
	src << "\t}\n";
	src << "}\n\n";
	
	// Add "close" method
	src << "void Game::close()\n{\n";
	src << "\tshutdown();\n\n";
	src << "\tif(m_renderer)\n\t{\n";
	src << "\t\tSDL_DestroyRenderer(m_renderer);\n";
	src << "\t\tm_renderer = nullptr;\n";
	src << "\t}\n\n";
	src << "\tif(m_window)\n\t{\n";
	src << "\t\tSDL_DestroyWindow(m_window);\n";
	src << "\t\tm_window = nullptr;\n";
	src << "\t}\n\n";
	src << "\tSDL_Quit();\n";
	src << "}\n\n";

	src.close();
}

void generateGameClass()
{
	generateGameHeader();
	generateGameSource();
}

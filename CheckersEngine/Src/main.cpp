#include <iostream>
#include "Game.h"
Game* game = nullptr;
int main(int argc, char* argv[]) {
	const int FPS = 60;
	const int framedelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;


	game = new Game();
	game->init("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1100, 1100, false);
	while (game->isRunning()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (framedelay > frameTime) {
			SDL_Delay(framedelay - frameTime);
		}
	}

	game->clean();
	return 0;
}
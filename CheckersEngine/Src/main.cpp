#include "Game.h"
#include "GameLogic/GameLogic.h"
#include <crtdbg.h>
Game *game = nullptr;
GameLogic gameLogic;

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int* p = new int[100];
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		//gameLogic.getBoard()->Display();
		
  /*      cout << "Num Black: " << gameLogic.getBoard()->getInstances('B').size() << endl;
        cout << "Num Red: " << gameLogic.getBoard()->getInstances('R').size() << endl;

        if(gameLogic.getCurrPlayer() == 'R')
            gameLogic.getPlayer().makeMove(gameLogic.getBoard());
        else
            gameLogic.getBot().makeMove(gameLogic.getBoard());

        gameLogic.changeTurns();

		game->setBoard(gameLogic.getBoard());*/
	
	}
	game->clean();
	system("PAUSE");
	return 0;
}
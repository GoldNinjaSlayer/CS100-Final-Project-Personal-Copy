#include "Game.h"
#include "GameLogic/GameLogic.h"
#include <chrono>
#include <thread>

Game *game = nullptr;
GameLogic gameLogic;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);
	game->handleEvents();
	game->update();
	while (gameLogic.update() != 0)
	{
		frameStart = SDL_GetTicks();
	//	game->handleEvents();
	//	game->update();
		//game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		//gameLogic.getBoard()->Display(); // Displays board in terminal
		game->setBoard(gameLogic.getBoard()); // Updates visual board based on terminal board
		
        cout << "Num Black: " << gameLogic.getBoard()->getInstances('B').size() << endl;
        cout << "Num Red: " << gameLogic.getBoard()->getInstances('R').size() << endl;

        if(gameLogic.getCurrPlayer() == 'R'){
            gameLogic.getPlayer().makeMove(gameLogic.getBoard());
		}
        else{
            gameLogic.getBot().makeMove(gameLogic.getBoard());
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		game->clearPieces(); //WIP
		game->handleEvents();
		
		game->render();
		game->update();
        gameLogic.changeTurns();

	
	}

	string test; //testing purposes
	cout << "type anything to close window" << endl;
	cin >> test;

	game->clean();

	delete game;

	return 0;
}
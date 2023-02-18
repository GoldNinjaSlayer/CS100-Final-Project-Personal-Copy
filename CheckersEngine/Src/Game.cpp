#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "GameLogic/Board.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

//auto& player(manager.addEntity());
//auto& wall(manager.addEntity());
//
auto& black(manager.addEntity());


auto& checkboard(manager.addEntity());
auto& red(manager.addEntity());
Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	IMG_Init(IMG_INIT_PNG);
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	
	//map = new Map();
	
	checkboard.addComponent<TransformComponent>(140,80,500,500,1);
	checkboard.addComponent<SpriteComponent>("assets/Checkerboard.png");


	//black.addComponent<TileComponent>(200, 200, 32, 32, 0);
	//black.addComponent<ColliderComponent>("black");
	red.addComponent<TileComponent>(165, 105, 60, 61, 1);
	red.addComponent<ColliderComponent>("red");
	red.addComponent<TileComponent>(65, 105, 60, 61, 1);
	red.addComponent<ColliderComponent>("red2");
	
	for(int i = 0; i < board->ROWS; i++){
		for(int j = 0; j < board->COLS; j++){
			if(board->checkers[i][j]->getColor() == 'R'){
				red.addComponent<TileComponent>(165+(10 * i), 105, 60, 61, 1);
				red.addComponent<ColliderComponent>("red" + i);
			}
		}
	}


	//player.addComponent<TransformComponent>();
	//player.addComponent<SpriteComponent>("assets/lucas.png");
	//player.addComponent<KeyboardController>();
	//player.addComponent<ColliderComponent>("player");

	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 100, 100, 1);
	//wall.addComponent<SpriteComponent>("assets/blackTile.png");
	//wall.addComponent<ColliderComponent>("wall");

}

void Game::handleEvents()
{


	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	//for (auto cc : colliders)
	//{
	//	Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	//
	//}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);


}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
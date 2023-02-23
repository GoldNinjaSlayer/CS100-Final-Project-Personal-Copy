#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace std;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::tileColliders;
std::vector<ColliderComponent*> Game::colliders;

auto& black(manager.addEntity());



auto& checkboard(manager.addEntity());
auto& red(manager.addEntity());

enum groupLabels : std::size_t
{
	groupTiles,
};

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
	initTiles();
	board = new Board(8);
	board->allowedMoves(board->getInstances('B'));
	board->allowedMoves(board->getInstances('R'));



	int x = 0;
	int y = 0;







	//black.addComponent<TileComponent>(200, 200, 32, 32, 0);
	//black.addComponent<ColliderComponent>("black");
	
	//for(int i = 0; i < 8; i++){
	//	for(int j = 0; j < 8; j++){
	//		if(board->getchecker(i,j)->getColor() == 'R'){
	//			red.addComponent<TileComponent>(160 + (55* j), 100 + (55 * i), 60, 60, 1);
	//			red.addComponent<ColliderComponent>("red");
	//		}
	//		if(board->getchecker(i,j)->getColor() == 'B'){
	//			black.addComponent<TileComponent>(160 + (55* j), 100 + (55 * i), 60, 60, 0);
	//			black.addComponent<ColliderComponent>("black");
	//		}
	//	}
	//}

	//player.addComponent<TransformComponent>();
	//player.addComponent<SpriteComponent>("assets/lucas.png");
	//player.addComponent<KeyboardController>();
	//player.addComponent<ColliderComponent>("player");


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

}

auto& tiles(manager.getGroup(groupTiles));

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
	delete[] board;
}

void Game::AddChecker(int id, int x, int y, int num, Checker* p) {
	auto& piece(manager.addEntity());
	piece.addComponent<TileComponent>(x, y, 60, 61, id);
	piece.addComponent<MouseController>();
	piece.addComponent<ColliderComponent>("piece " + to_string(num));
	piece.addComponent<CheckerLinker>(p);
	piece.addComponent<CheckerLocker>();

}

void Game::AddTile(int x, int y, int id, int i, int j)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TransformComponent>(x, y, 40, 40, 1);
	tile.addComponent<SpriteComponent>("assets/blackTile.png");
	tile.addComponent<ColliderComponent>("tile " + to_string(id));
	tile.addComponent<TileLinker>(i, j);
	//tile.addGroup(groupTiles);
	

}

void Game::setBoard(Board* board){
	this->board = board;
}

void Game::initTiles()
{
	int x = 0;
	//draws first 3
	for (int i = 0; i < 4; i++) {
		AddTile(172 + (i * 113), 110, x++, 0,i);
	}

	for (int i = 0; i < 4; i++) {
		AddTile(228 + (i * 113), 172, x++, 1, i);
	}

	for (int i = 0; i < 4; i++) {

		AddTile(172 + (i * 111), 226, x++, 2, i);
	}

	//Draws middle 2

	for (int i = 0; i < 4; i++) {
		AddTile(228 + (i * 113), 280, x++, 3, i);
	}

	for (int i = 0; i < 4; i++) {
		AddTile(172 + (i * 113), 337, x++, 4, i);
	}




	//Draws last 3
	for (int i = 0; i < 4; i++) {
		AddTile(228 + (i * 113), 390, x++, 5, i);
	}

	for (int i = 0; i < 4; i++) {
		AddTile(172 + (i * 113), 446, x++, 6, i);
	}

	for (int i = 0; i < 4; i++) {

		AddTile(228 + (i * 111), 508, x++, 7, i);
	}
}
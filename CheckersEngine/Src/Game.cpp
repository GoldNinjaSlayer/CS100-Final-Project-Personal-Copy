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


	int x = 0;

	//Draws red checker pieces to the board
	for (int i = 0; i < 4; i++) {
		//AddChecker(1, 220+ (i * 110), 105);
		AddTile(228 + (i * 113), 110, x++);
	}
	
	for (int i = 0; i < 4; i++) {
		//AddChecker(1,165+(i * 110), 160);
		AddTile(172 + (i * 113), 172, x++);
	}

	for (int i = 0; i < 4; i++) {
		
		AddTile(228 + (i * 111), 226, x++);
		AddChecker(1, 220 + (i * 110), 215);
	}


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
}

void Game::AddChecker(int id, int x, int y) {
	auto& piece(manager.addEntity());
	piece.addComponent<TileComponent>(x, y, 60, 61, id);
	piece.addComponent<MouseController>();
	piece.addComponent<ColliderComponent>("piece");
	piece.addComponent<CheckerController>();
}

void Game::AddTile(int x, int y, int id)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TransformComponent>(x, y, 40, 40, 1);
	//tile.addComponent<SpriteComponent>("assets/blackTile.png");
	tile.addComponent<ColliderComponent>("tile " + to_string(id));
	cout << tile.getComponent<ColliderComponent>().tag << endl;
	//tile.addGroup(groupTiles);
	

}



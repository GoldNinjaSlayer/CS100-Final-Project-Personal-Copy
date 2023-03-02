#include "Game.h"
#include "TextureManager.h"
#include "ECS/KeyboardController.h"
#include "Collision.h"
#include "ECS/TileComponent.h"
#include "ECS/ColliderComponent.h"
using namespace std;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*>Game::colliders;
Manager manager;
Manager ColliderManager;

auto& board(manager.addEntity());
auto& player(manager.addEntity());
//auto& wall(manager.addEntity());
Game::Game() {
	window = nullptr;
	running = false;
}
Game::~Game() {}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems initialized..." << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created" << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer) {
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			cout << "Renderer created" << endl;
		}
		running = true;
	}
	else { running = false; }
	map = new Map();

	player.addComponent<TransformComponent>(70, 70);
	player.addComponent<KeyboardController>();
	player.addComponent<SpriteComponent>().setTex("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/red-piece.png", 60, 60);
	player.addComponent<ColliderComponent>("player");

	board.addComponent<TransformComponent>(250.0f, 250.0f, 500, 500);
	board.addComponent<SpriteComponent>().setTex("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/CheckerBoard.png", 500, 500);

	/*wall.addComponent<TransformComponent>(300.0f, 300.0f,70,70);
	wall.addComponent<SpriteComponent>("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/WhiteTile.png");
	wall.addComponent<ColliderComponent>("wall");
	*/

}
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
	default:
		break;
	}

}
void Game::update() {
	manager.refresh();
	manager.update();
	ColliderManager.refresh();
	ColliderManager.update();

	//if (player.getComponent<TransformComponent>().getXPos() >= 100) {
	//	player.getComponent<SpriteComponent>().setTex("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/ness.png",171,250);
	//}
	////cout << player.getComponent<ColliderComponent>().collider.x << ", "<< wall.getComponent<ColliderComponent>().collider.x<<endl;
	/*for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}*/


}
void Game::render() {
	SDL_RenderClear(Game::renderer);
	//this is where we add stuff to render
	//map->DrawMap();
	manager.draw();
	ColliderManager.draw();

	SDL_RenderPresent(Game::renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	cout << "Game cleaned" << endl;
}
bool Game::isRunning() {
	return running;
}

void Game::AddTile(int x, int y) {
	auto& tile(ColliderManager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32);
	tile.addComponent<ColliderComponent>("magnet");
	Game::colliders.push_back(&tile.getComponent<ColliderComponent>());

}
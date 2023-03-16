#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "ECS/ButtonComponent.h"

using namespace std;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
Board* Game::board = nullptr;
Manager manager;
SDL_Event Game::event;

std::vector<Entity*> Game::tiles;

std::vector<Entity*> Game::checkersEntities;
std::vector<ColliderComponent*> Game::colliders;


auto& black(manager.addEntity());
auto& Logic(manager.addEntity());

auto& menuBG(manager.addEntity());
auto& logo(manager.addEntity());
auto& buttonStart(manager.addEntity());
auto& buttonQuit(manager.addEntity());

auto& red(manager.addEntity());

enum State {
    Menu,
    Level0,
    GameInProgress
};

State state = Menu;

int groupTiles = 0;
int groupCheckers = 1;
int groupMainMenu = 999;

vector<int> groupIds = {groupTiles, groupCheckers, groupMainMenu};

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

    //display main menu

    menuBG.addComponent<TransformComponent>(-15, 0, 2560, 2560, 0.32);
    menuBG.addComponent<SpriteComponent>("assets/menu.jpeg");
    menuBG.addGroup(groupMainMenu);

    logo.addComponent<TransformComponent>(-15, 0, 2560, 2560, 0.32);
    logo.addComponent<SpriteComponent>("assets/title.png");
    logo.addGroup(groupMainMenu);

    buttonStart.addComponent<TransformComponent>(width/2 - 508/4, height/2 + 40, 112, 508, 0.5);
    buttonStart.addComponent<SpriteComponent>();
    buttonStart.addComponent<ButtonComponent>("assets/GUI/Green_Button.png", "assets/GUI/Green_Button_Pressed.png", "assets/GUI/Green_Button_Hovered.png");
    buttonStart.getComponent<ButtonComponent>().addCallback(this, &Game::setStateLevel0);
    //buttonStart.addComponent<TextComponent>();
    buttonStart.addGroup(groupMainMenu);

    buttonQuit.addComponent<TransformComponent>(width/2 - 508/4, height/2 + 40 + 112/2 + 10, 112, 508, 0.5);
    buttonQuit.addComponent<SpriteComponent>();
    buttonQuit.addComponent<ButtonComponent>("assets/GUI/Green_Button.png", "assets/GUI/Green_Button_Pressed.png", "assets/GUI/Green_Button_Hovered.png");
    buttonQuit.addGroup(groupMainMenu);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
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

    if(state == Level0){
        state = GameInProgress;
        startGame();
    }
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
	delete[] board;
}

void Game::AddChecker(int id, int x, int y, int num, Checker* p) {
	auto& piece(manager.addEntity());
	piece.addComponent<TileComponent>(x, y, 60, 61, id);
	piece.addComponent<MouseController>();
	piece.addComponent<ColliderComponent>("piece " + to_string(num));
	piece.addComponent<CheckerLinker>(p);
	piece.addComponent<CheckerLocker>();
	piece.addGroup(groupCheckers);
}

void Game::AddTile(int x, int y, int i, int j)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TransformComponent>(x, y, 40, 40, 1);
	//tile.addComponent<SpriteComponent>("assets/blackTile.png");
	tile.addComponent<ColliderComponent>("tile " + to_string((i * 8) + j));
	tile.addComponent<TileLinker>(i, j);
	tile.addGroup(groupTiles);
}

void Game::setBoard(Board* board) {
	this->board = board;
}

void Game::initTiles()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			AddTile((-56 * ((i + 1) % 2) + 228 + (j * 113)), 110 + (i * 57), i, j * 2 + (i % 2));
		}
	}
}

void Game::startGame() {
    resetScreen();
    auto& bg(manager.addEntity());
    bg.addComponent<TransformComponent>(0, 0, 2560, 2560, 0.32);
    bg.addComponent<SpriteComponent>("assets/bg1.jpg");

    auto& checkboard(manager.addEntity());
    checkboard.addComponent<TransformComponent>(140, 80, 500, 500, 1);
    checkboard.addComponent<SpriteComponent>("assets/Checkerboard.png");

    initTiles();
    tiles = manager.getGroup(groupTiles);
    board = new Board(8);
    checkersEntities = manager.getGroup(groupCheckers);
    board->allowedMoves(board->getInstances('B'));
    board->allowedMoves(board->getInstances('R'));
    Logic.addComponent<LogicComponent>();

    auto& caveman(manager.addEntity());
    caveman.addComponent<TransformComponent>(550, 350, 422, 403, 1);
    caveman.addComponent<SpriteComponent>("assets/caveman-idle.png");
    caveman.addComponent<ButtonComponent>("assets/caveman-idle.png", "assets/caveman-idle.png", "assets/caveman-idle-hovered.png");
}

void Game::resetScreen() {
    cout << "clearing screen..." << endl;

    menuBG.destroy();
    logo.destroy();
    buttonStart.destroy();
    buttonQuit.destroy();
}

void Game::setStateLevel0() {
    state = Level0;
}
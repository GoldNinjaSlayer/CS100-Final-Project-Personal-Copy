#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h" 
#include <vector> 
#include "GameLogic/Board.h"
#include "ECS/ECS.h"

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	void setBoard(Board* board);
	void clearPieces();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;

	Board *board = new Board(8); // creates board object
	vector<Component> tileComponent; //WIP
	vector<Component> colliderComponent; //WIP
	
};
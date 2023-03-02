#pragma once
#include "Game.h"

class Map {
public:
	Map();
	~Map();

	void LoadMap(int[11][11]);
	void DrawMap();
private:

	SDL_Texture* text1;
	SDL_Texture* text2;
	SDL_Texture* text3;

	SDL_Rect srcR, destR;

	int map[20][25];

};
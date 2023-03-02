#include "Map.h"
#include "TextureManager.h"
#include "ECS/ColliderComponent.h"
#include "ECS/ECS.h"

int lvl1[11][11] = {
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0}

};
Map::Map() {
	text1 = TextureManager::LoadTexture("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/blackTile.png");
	text2 = TextureManager::LoadTexture("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/redTile.png");
	text3 = TextureManager::LoadTexture("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/WhiteTile.png");
	LoadMap(lvl1);
	srcR.w = srcR.h = 32;
	srcR.x = srcR.y = 0;
	destR.h = 75;
	destR.w = 75;
	destR.x = destR.y = 0;
}
Map::~Map() {
	SDL_DestroyTexture(text1);
	SDL_DestroyTexture(text2);
}
void Map::LoadMap(int arr[11][11]) {
	for (int row = 0;row < 10;row++) {
		for (int col = 0;col < 10;col++) {
			map[row][col] = arr[row][col];
		}
	}

}
void Map::DrawMap() {
	int type = 0;
	for (int row = 0;row < 10;row++) {
		for (int col = 0;col < 10;col++) {
			type = map[row][col];
			destR.x = col * destR.w;
			destR.y = row * destR.h;
			switch (type) {
			case 1:
				//Game::AddTile((2 * destR.x + destR.w) / 2, (2 * destR.y + destR.h) / 2);
				//TextureManager::Draw(text1,srcR, destR);
				break;
			case 0:
				//TextureManager::Draw(text2, srcR, destR);
				break;
			default:
				break;

			}
		}
	}


}
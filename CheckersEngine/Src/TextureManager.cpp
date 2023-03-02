#include "Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) {

	SDL_Surface* tmpSurface = IMG_Load(filename);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;

}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcR, SDL_Rect destR) {
	SDL_RenderCopy(Game::renderer, tex, &srcR, &destR);
}
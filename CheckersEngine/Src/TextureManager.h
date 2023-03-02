#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture*, SDL_Rect, SDL_Rect);
};
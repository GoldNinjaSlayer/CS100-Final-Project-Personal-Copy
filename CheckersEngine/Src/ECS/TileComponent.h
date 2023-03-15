#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		switch (tileID)
		{
		case 0:
			path = "../assets/checkersPieces/blackPieceNormal.png";
			break;
		case 1:
			path = "../assets/checkersPieces/redPieceNormal.png";
			break;
		case 2:
			path = "../assets/checkersPieces/blackPieceKing.png";
			break;
		case 3:
			path = "../assets/checkersPieces/redPieceKing.png";
			break;
		case 4:
			path = "assets/blackTile.png";
			break;
		default:
			break;
		}
	}
	~TileComponent()
	{
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};
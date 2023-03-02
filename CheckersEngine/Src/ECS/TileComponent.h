#pragma once
#include "TransformComponent.h"
#include "SDL.h"
#include "SpriteComponent.h"

class TileComponent :public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	//TileComponent() = default;

	TileComponent(int x, int y, int w, int h) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
	}

	void init() {
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>("C:/Users/User/source/repos/GameLoop1/GameLoop1/assets/WhiteTile.png");
		sprite = &entity->getComponent<SpriteComponent>();
	}
};

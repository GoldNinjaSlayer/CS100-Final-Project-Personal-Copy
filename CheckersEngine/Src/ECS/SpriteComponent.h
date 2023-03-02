#pragma once
#include "TransformComponent.h"
#include "../TextureManager.h"
class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcR, destR;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* texturePath) {

		setTex(texturePath, 32, 32);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void init()override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		srcR.x = srcR.y = 0;
		destR.w = transform->width;
		destR.h = transform->height;
	}
	void setTex(const char* newTex, int srcwidth, int srcheight) {// sets new source height and width to read in size of new textures. Also sets new texture path
		texture = TextureManager::LoadTexture(newTex);
		srcR.w = srcwidth;
		srcR.h = srcheight;

	}
	void update()override {//TransformComponent is added to manager first so it is updated first and then the SpriteComponenet updates based on its new positions given by the transformation
		destR.x = static_cast<int>(transform->getXPos());
		destR.y = static_cast<int>(transform->getYPos());
		destR.w = transform->width;
		destR.h = transform->height;
	}
	void draw()override {
		TextureManager::Draw(texture, srcR, destR);
	}


};


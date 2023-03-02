#pragma once
#include "ECS.h"
#include "Vector2D.h"
struct TransformComponent :public Component {

	Vector2D position;// this is the part of transformation that uses Vector2D operators
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 5;

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(int w, int h) {
		height = h;
		width = w;
	}
	TransformComponent(float x, float y, int w, int h) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
	}
	TransformComponent() {
		velocity.Zero();
		position.Zero();
	}
	void setPos(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void init()override {
		velocity.Zero();
	}
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
	float getYPos() {
		return position.y;
	}
	float getXPos() {
		return position.x;
	}

};

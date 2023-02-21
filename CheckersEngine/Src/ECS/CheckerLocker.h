#pragma once
#include "ECS.h"
#include "../Collision.h"
#include "ColliderComponent.h"

//#include "../Game.h"
//#include <iostream>
using namespace std;


class CheckerLocker : public Component
{
private:
    ColliderComponent* collider;
    TransformComponent* transform;
    MouseController* mouse;
public:
    void init() override;
    void update() override;
};


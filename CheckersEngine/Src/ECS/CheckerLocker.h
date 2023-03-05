#pragma once
#include "ECS.h"
#include "../Collision.h"
#include "ColliderComponent.h"
#include <vector>
#include "CheckerLinker.h"


//#include "../Game.h"
//#include <iostream>
using namespace std;

//Class controls logic to automatically snap pieces into a tile
class CheckerLocker : public Component
{
private:
    ColliderComponent* collider;
    TransformComponent* transform;
    MouseController* mouse;
    CheckerLinker* position;
    Entity* currentTile;

    //Helper functions
    bool checkCollision(Entity* tile);
    void swapPiece(Entity* tile);
    void lockPiece(Entity* tile);
    void capturePiece(Entity* checker);


public:
    void init() override;
    void update() override;
    void moveLogic();
};

//todo: Need to gain access to a pieces available moves and only highlight the tiles that piece can go to
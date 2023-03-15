#pragma once
#include "ECS.h"
#include "Components.h"

#include "../Game.h"
#include "../GameLogic/GameLogic.h"
#include <iostream>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;

//Class controls logic to automatically snap pieces into a tile
class TileLinker : public Component
{
private:
    coord pos;
    Entity* piece;
public:

    TileLinker(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }

    coord getPos() const
    {
        return pos;
    }
};


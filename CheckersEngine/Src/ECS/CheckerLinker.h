#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Game.h"

#include <iostream>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;


class CheckerLinker : public Component
{
private:
    Checker* piece;
    
public:


    CheckerLinker(Checker* piece)
    {
        this->piece = piece;
        //piece->guiChecker = &this->entity->getComponent<SpriteComponent>();
    }

    Checker* getPiece() const
    {
        return piece;
    }
};


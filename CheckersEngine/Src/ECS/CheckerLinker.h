#pragma once
#include "ECS.h"
#include "Components.h"

#include "../Game.h"
#include <iostream>
using namespace std;

//Class controls logic to automatically snap pieces into a tile
class CheckerLinker : public Component
{
private:
    
public:
    void init() override;
    void update() override;
};


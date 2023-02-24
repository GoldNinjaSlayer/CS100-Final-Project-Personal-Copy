//
// Created by theff on 2/21/2023.
//

#ifndef CHECKERSENGINE_STATE_H
#define CHECKERSENGINE_STATE_H


#include "SDL.h"

class State {
public:
    SDL_Texture* background;
    State();
    virtual ~State();
    virtual void enter() = 0;
    virtual void update() = 0;
};

class Menu : public State {
public:
    Menu();
    virtual ~Menu();
    void enter();
    void update();
};

class Options : public State {

};


#endif //CHECKERSENGINE_STATE_H

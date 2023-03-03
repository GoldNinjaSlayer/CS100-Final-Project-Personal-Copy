//
// Created by theff on 2/21/2023.
//

#ifndef CHECKERSENGINE_BUTTONCOMPONENT_H
#define CHECKERSENGINE_BUTTONCOMPONENT_H


#include <string>
#include "ECS.h"
#include "SpriteComponent.h"

enum ButtonState {
    NORMAL = 0,
    PRESSED = 1,
    HOVERED = 2
};

class ButtonComponent : public SpriteComponent{
private:
    SpriteComponent *sprite;
    TransformComponent *transform;

    ButtonState currentState;
    std::string texture;

    bool isInButton = false;

    void (Game::*CallBack)();
    Game* game;


public:
    ButtonComponent(std::string path){
        currentState = NORMAL;
        texture = path;
    };
    ~ButtonComponent() {};

    void addCallback(Game* g, void (Game::*function)()){
        CallBack = function;
        game = g;
    }

    void init() override {
        sprite = &entity->getComponent<SpriteComponent>();
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {

        if(Game::event.type == SDL_MOUSEMOTION){
            //mouse position is only captured if it is in motion
            int mouseX = Game::event.motion.x;
            int mouseY = Game::event.motion.y;
            int buttonWidth = transform->width;
            int buttonHeight = transform->height;
            float buttonX = transform->position.x;
            float buttonY = transform->position.y;

            isInButton = (mouseX >= buttonX && mouseX <= buttonX + buttonWidth) &&
                         (mouseY >= buttonY && mouseY <= buttonY + buttonHeight);
        }

        if(isInButton){
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                //pressed
                currentState = PRESSED;

            }
            else if(Game::event.type == SDL_MOUSEBUTTONUP){
                //released
                currentState = NORMAL;
                if(CallBack != nullptr){
                    (game->*CallBack)();
                }
            }
            else if(currentState != PRESSED){
                //hovering
                currentState = HOVERED;
            }
        }
        else{
            //not within button
            currentState = NORMAL;
        }

        sprite->setTex((texture + to_string(currentState) + ".png").c_str());
    }
};


#endif //CHECKERSENGINE_BUTTONCOMPONENT_H

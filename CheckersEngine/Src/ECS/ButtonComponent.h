//
// Created by theff on 2/21/2023.
//

#ifndef CHECKERSENGINE_BUTTONCOMPONENT_H
#define CHECKERSENGINE_BUTTONCOMPONENT_H


#include <string>
#include "ECS.h"
#include "SpriteComponent.h"

enum ButtonState {
    UNKNOWN = -1,
    NORMAL = 0,
    PRESSED = 1,
    HOVERED = 2
};

class ButtonComponent : public Component{
private:
    SpriteComponent *sprite;
    TransformComponent *transform;

    ButtonState currentState = UNKNOWN;
    const char* texturePathNormal;
    const char* texturePathPressed;
    const char* texturePathHovered;

    bool isInButton = false;

    void (Game::*CallBack)() = nullptr;
    Game* game;

public:
    ButtonComponent(const char* normal, const char* pressed){
        texturePathNormal = normal;
        texturePathPressed = pressed;
        texturePathHovered = texturePathNormal;
    };

    ButtonComponent(const char* normal, const char* pressed, const char* hovered){
        texturePathNormal = normal;
        texturePathPressed = pressed;
        texturePathHovered = hovered;
    };

    ~ButtonComponent() {};

    void addCallback(Game* g, void (Game::*function)()){
        CallBack = function;
        game = g;
    }

    void init() override {
        sprite = &entity->addComponent<SpriteComponent>();
        transform = &entity->getComponent<TransformComponent>();
        sprite->setTex(texturePathNormal);
    }

    void update() override {

        if(Game::event.type == SDL_MOUSEMOTION){
            //mouse position is only captured if it is in motion
            int mouseX = Game::event.motion.x;
            int mouseY = Game::event.motion.y;
            int buttonWidth = transform->width * transform->scale;
            int buttonHeight = transform->height * transform->scale;
            float buttonX = transform->position.x;
            float buttonY = transform->position.y;

            isInButton = (mouseX >= buttonX && mouseX <= buttonX + buttonWidth) &&
                         (mouseY >= buttonY && mouseY <= buttonY + buttonHeight);
        }

        if(isInButton){
            if(Game::event.type == SDL_MOUSEBUTTONDOWN){
                //pressed
                currentState = PRESSED;
                sprite->setTex(texturePathPressed);
            }
            else if(Game::event.type == SDL_MOUSEBUTTONUP){
                //released
                currentState = NORMAL;
                sprite->setTex(texturePathNormal);

                if(CallBack != nullptr){
                    //THIS IS BROKEN, calls the function, but messes up the components due to the way it calls back
                    (game->*CallBack)();
                }
            }
            else if(currentState != PRESSED){
                //hovering
                currentState = HOVERED;
                sprite->setTex(texturePathHovered);
            }
        }
        else{
            //not within button
            if(currentState == NORMAL)
                return;
            currentState = NORMAL;
            sprite->setTex(texturePathNormal);
        }
    }
};


#endif //CHECKERSENGINE_BUTTONCOMPONENT_H

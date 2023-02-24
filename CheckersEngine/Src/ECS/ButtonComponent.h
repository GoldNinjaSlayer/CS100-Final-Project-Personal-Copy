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


public:
    ButtonComponent(std::string path){
        currentState = NORMAL;
        texture = path;
    };
    ~ButtonComponent() {};

    void init() override {
        sprite = &entity->getComponent<SpriteComponent>();
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        //pressed
        if(Game::event.type == SDL_MOUSEBUTTONDOWN){
            currentState = PRESSED;
        }

        //released
        if(Game::event.type == SDL_MOUSEBUTTONUP){
            currentState = NORMAL;
        }

        //hovering
        int mouseX = Game::event.motion.x;
        int mouseY = Game::event.motion.y;
        int buttonWidth = transform->width;
        int buttonHeight = transform->height;
        float buttonX = transform->position.x;
        float buttonY = transform->position.y;
        /*
        if((mouseX >= buttonX && mouseX <= buttonX + buttonWidth) &&
                (mouseY >= buttonY && mouseY <= buttonY + buttonHeight)) {
            currentState = HOVERED;
        }else{
            currentState = NORMAL;
        }
         */

        sprite->setTex((texture + to_string(currentState) + ".png").c_str());
    }
};


#endif //CHECKERSENGINE_BUTTONCOMPONENT_H

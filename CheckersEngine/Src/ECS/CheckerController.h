

#include "ECS.h"
#include "Components.h"
#include "Collision.h"
#include "../Game.h"
#include <iostream>



class CheckerController : public Component
{
private:
    ColliderComponent* collider = nullptr;
    TransformComponent* transform = nullptr;
    MouseController* mouse = nullptr;

public:
    void init() override
    {
        collider = &entity->getComponent<ColliderComponent>();
        transform = &entity->getComponent<TransformComponent>();
        mouse = &entity->getComponent<MouseController>();
    }

    void update() override
    {
        // Check if this checker is being dragged by the mouse
        if (mouse->isMouseDragging)
        {
            // Set the checker's position to the mouse position
            transform->position.x = mouse->lastMouseX - (transform->width / 2);
            transform->position.y = mouse->lastMouseY - (transform->height / 2);

            // Loop over all the colliders to check for a collision
            for (auto otherCollider : Game::tileColliders)
            {
                
                if (otherCollider != collider && Collision::AABB(*collider, *otherCollider))
                {
                    // If there's a collision, snap this checker to the other collider's position
                 /*   transform->position.x = otherCollider->collider.x + (otherCollider->collider.w / 2) - (transform->width / 2);
                    transform->position.y = otherCollider->collider.y + (otherCollider->collider.h / 2) - (transform->height / 2);
                    break;*/
                }
            }
        }
    }
};

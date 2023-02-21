#include "CheckerController.h"
#include "ColliderComponent.h"
#include "MouseController.h"
#include "TransformComponent.h"
#include <iostream>

using namespace std;
void CheckerController::init() 
{
    collider = &entity->getComponent<ColliderComponent>();

    transform = &entity->getComponent<TransformComponent>();
    mouse = &entity->getComponent<MouseController>();
    //cout << "In checkercontroller: " << collider->collider.x << endl;
}

void CheckerController::update() 
{

    // Check if this checker is being dragged by the mouse
    if (!mouse->isMouseDragging)
    {
        // Set the checker's position to the mouse position


        // Loop over all the colliders to check for a collision
        for (auto& otherCollider : Game::tileColliders)
        {

            if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
            {
                //    If there's a collision, snap this checker to the other collider's position
                    
                    transform->position.x = otherCollider->collider.x + (otherCollider->collider.w / 2) - (transform->width / 2);
                    transform->position.y = otherCollider->collider.y + (otherCollider->collider.h / 2) - (transform->height / 2);
                break;
            }
        }
    }
}
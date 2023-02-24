#include "CheckerLocker.h"
#include "ColliderComponent.h"
#include "MouseController.h"
#include "TransformComponent.h"
#include <iostream>

using namespace std;
void CheckerLocker::init()
{
    collider = &entity->getComponent<ColliderComponent>();

    transform = &entity->getComponent<TransformComponent>();
    mouse = &entity->getComponent<MouseController>();
    position = &entity->getComponent<CheckerLinker>();
    
    //cout << "In checkercontroller: " << collider->collider.x << endl;
}

void CheckerLocker::update()
{
    for (auto& tile : Game::tiles) {
        if (position->getPiece()->getPosition() == tile->getComponent<TileLinker>().getPos())
        {
            currentTile = tile;
            break;
        }
    }
    

    //if (mouse->isMouseDragging)
    //{
    //    for (auto m : position->getPiece()->moves)
    //    {
    //        cout << m << endl;
    //    }
    //}
 
    // Check if this checker is being dragged by the mouse
    if (!mouse->isMouseDragging)
    {
        bool collisionDetected = false;

        // Loop over all the colliders to check for a collision
        for (auto& tile : Game::tiles)
        {
            bool collisionDetected = false;
            ColliderComponent* otherCollider = &tile->getComponent<ColliderComponent>();

            if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
            {
                //    If there's a collision, snap this checker to the other collider's position
                if (position->getPiece()->moves.find(tile->getComponent<TileLinker>().getPos()) != position->getPiece()->moves.end() || tile->getComponent<TileLinker>().getPos() == position->getPiece()->getPosition())
                {
                    transform->position.x = otherCollider->collider.x + (otherCollider->collider.w / 2) - (transform->width / 2);
                    transform->position.y = otherCollider->collider.y + (otherCollider->collider.h / 2) - (transform->height / 2);
                    collisionDetected = true;
                    break;
                }
            }

            if (!collisionDetected)
            {
                transform->position.x = currentTile->getComponent<ColliderComponent>().collider.x + (currentTile->getComponent<ColliderComponent>().collider.w / 2) - (transform->width / 2);
                transform->position.y = currentTile->getComponent<ColliderComponent>().collider.y + (currentTile->getComponent<ColliderComponent>().collider.h / 2) - (transform->height / 2);
            }
        }

    }


}
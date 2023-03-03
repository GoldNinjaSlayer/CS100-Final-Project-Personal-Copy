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


    // Check if this checker is being dragged by the mouse

    //if (mouse->isMouseDragging)
    //{
    //    if (position->getPiece()->canCapture)
    //    {
    //        cout << position->getPiece()->getPosition() << " can capture!" << endl;
    //        cout << "Tile that needs lock" << endl;
    //        for (auto& dest : position->getPiece()->moves)
    //        {
    //            int calcx = dest.x - position->getPiece()->getPosition().x;
    //            int calcy = dest.y - position->getPiece()->getPosition().y;

    //            cout << "(" << dest.x + calcx << "," << dest.y + calcy << ")" << endl;
    //        }

    //    }

    //    cout << "Available moves" << endl;
    //    for (auto& move : position->getPiece()->moves)
    //    {
    //        cout << move << endl;
    //    }
    //}

    if (!mouse->isMouseDragging)
    {
        bool collisionDetected = false;

        // Loop over all the colliders to check for a collision
        for (auto& tile : Game::tiles)
        {

            ColliderComponent* otherCollider = &tile->getComponent<ColliderComponent>();
            if (!position->getPiece()->canCapture)
            {
                if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
                {
                    //    If there's a collision, snap this checker to the other collider's position
                    if (position->getPiece()->moves.find(tile->getComponent<TileLinker>().getPos()) != position->getPiece()->moves.end() || tile->getComponent<TileLinker>().getPos() == position->getPiece()->getPosition())
                    {
                        transform->position.x = otherCollider->collider.x + (otherCollider->collider.w / 2) - (transform->width / 2);
                        transform->position.y = otherCollider->collider.y + (otherCollider->collider.h / 2) - (transform->height / 2);

                        if (tile->getComponent<TileLinker>().getPos() != position->getPiece()->getPosition())
                        {

                            Game::board->swap(position->getPiece(), Game::board->getchecker(tile->getComponent<TileLinker>().getPos().x, tile->getComponent<TileLinker>().getPos().y));

                            Game::board->allowedMoves(Game::board->getInstances('B'));
                            Game::board->allowedMoves(Game::board->getInstances('R'));
                        }
                        collisionDetected = true;
                        break;
                    }
                }
            }
            else
            {
                
                bool correctPos = false;
                int calcx;
                int calcy;
                for (auto& dest : position->getPiece()->moves)
                {
                    calcx = dest.x - position->getPiece()->getPosition().x;
                    calcy = dest.y - position->getPiece()->getPosition().y;

                    if (tile->getComponent<TileLinker>().getPos().x == dest.x + calcx && tile->getComponent<TileLinker>().getPos().y == dest.y + calcy)
                    {
                        correctPos = true;
                        //cout << "CORRECT POS" << endl;
                        break;
                    }
                }

                if (correctPos)
                {

                    if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
                    {
                        transform->position.x = otherCollider->collider.x + (otherCollider->collider.w / 2) - (transform->width / 2);
                        transform->position.y = otherCollider->collider.y + (otherCollider->collider.h / 2) - (transform->height / 2);

                        for (auto& checker : Game::checkersEntities)
                        {
                            cout << checker->getComponent<CheckerLinker>().getPiece()->getPosition().x << " = " << tile->getComponent<TileLinker>().getPos().x - calcx << "?" << endl;

                            if ((checker->getComponent<CheckerLinker>().getPiece()->getPosition().x == (tile->getComponent<TileLinker>().getPos().x - calcx)) && (checker->getComponent<CheckerLinker>().getPiece()->getPosition().y == (tile->getComponent<TileLinker>().getPos().y - calcy)))
                            {

                                checker->getComponent<SpriteComponent>().destroyTex();
                                Game::board->capture(position->getPiece(), checker->getComponent<CheckerLinker>().getPiece());
                                Game::board->allowedMoves(Game::board->getInstances('B'));
                                Game::board->allowedMoves(Game::board->getInstances('R'));
                                break;
                            }
                        }
                        collisionDetected = true;
                        break;
                    }
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

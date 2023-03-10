#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class LogicComponent : public Component
{
private:
	MouseController* mouse;
    bool mouseHovering(Entity* component);
    void swapPiece(Entity* tile, Checker* checker);
    void capturePiece(Checker* checker1, Entity* checker2);
    void playerMove();
    void botMove();
    AI bot;

public:
    void init() override;
    void update() override;
};

//bool CheckerLocker::checkCollision(Entity* tile)
//{
//
//    ColliderComponent* otherCollider = &tile->getComponent<ColliderComponent>();
//    if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
//    {
//        return true;
//    }
//
//    return false;
//
//
//}
//
//void CheckerLocker::swapPiece(Entity* tile)
//{
//
//    Game::board->swap(position->getPiece(), Game::board->getchecker(tile->getComponent<TileLinker>().getPos().x, tile->getComponent<TileLinker>().getPos().y), false);
//
//    Game::board->allowedMoves(Game::board->getInstances('B'));
//    Game::board->allowedMoves(Game::board->getInstances('R'));
//}
//
//void CheckerLocker::capturePiece(Entity* checker)
//{
//    checker->getComponent<SpriteComponent>().destroyTex();
//    Game::board->capture(position->getPiece(), checker->getComponent<CheckerLinker>().getPiece());
//    Game::board->allowedMoves(Game::board->getInstances('B'));
//    Game::board->allowedMoves(Game::board->getInstances('R'));
//}
//
//void CheckerLocker::lockPiece(Entity* tile)
//{
//    transform->position.x = tile->getComponent<ColliderComponent>().collider.x + (tile->getComponent<ColliderComponent>().collider.w / 2) - (transform->width / 2);
//    transform->position.y = tile->getComponent<ColliderComponent>().collider.y + (tile->getComponent<ColliderComponent>().collider.h / 2) - (transform->height / 2);
//}
//
//void CheckerLocker::moveLogic()
//{
//        if (!mouse->isMouseDragging)
//        {
//            bool collisionDetected = false;
//
//            // Loop over all the colliders to check for a collision
//            for (auto& tile : Game::tiles)
//            {
//
//                if (!position->getPiece()->canCapture)
//                {
//                    if (checkCollision(tile))
//                    {
//                        //    If there's a collision, snap this checker to the other collider's position
//                        bool canMove = true;
//                        for (auto c : Game::checkersEntities)
//                        {
//                            if (c->getComponent<CheckerLinker>().getPiece()->canCapture && c->getComponent<CheckerLinker>().getPiece()->getColor() == position->getPiece()->getColor())
//                            {
//                                canMove = false;
//                                break;
//                            }
//                        }
//                        if (position->getPiece()->getColor() == Game::board->getTurn() && position->getPiece()->moves.find(tile->getComponent<TileLinker>().getPos()) != position->getPiece()->moves.end() && canMove || tile->getComponent<TileLinker>().getPos() == position->getPiece()->getPosition())
//                        {
//                            lockPiece(tile);
//
//                            {
//                                if (tile->getComponent<TileLinker>().getPos() != position->getPiece()->getPosition())
//                                    swapPiece(tile);
//                            }
//                            collisionDetected = true;
//                            break;
//                        }
//                    }
//                }
//                else
//                {
//
//                    bool correctPos = false;
//                    int calcx;
//                    int calcy;
//                    for (auto& dest : position->getPiece()->moves)
//                    {
//                        calcx = dest.x - position->getPiece()->getPosition().x;
//                        calcy = dest.y - position->getPiece()->getPosition().y;
//
//                        if (tile->getComponent<TileLinker>().getPos().x == dest.x + calcx && tile->getComponent<TileLinker>().getPos().y == dest.y + calcy)
//                        {
//                            correctPos = true;
//
//                            break;
//                        }
//                    }
//
//                    if (correctPos)
//                    {
//
//                        if (checkCollision(tile))
//                        {
//                            lockPiece(tile);
//
//                            for (auto& checker : Game::checkersEntities)
//                            {
//
//                                if ((checker->getComponent<CheckerLinker>().getPiece()->getPosition().x == (tile->getComponent<TileLinker>().getPos().x - calcx)) && (checker->getComponent<CheckerLinker>().getPiece()->getPosition().y == (tile->getComponent<TileLinker>().getPos().y - calcy)))
//                                {
//
//                                    capturePiece(checker);
//                                    break;
//                                }
//                            }
//                            collisionDetected = true;
//                            break;
//                        }
//                    }
//
//
//
//
//                }
//
//                if (!collisionDetected)
//                {
//                    lockPiece(currentTile);
//                }
//            }
//
//        }
//}
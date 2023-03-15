#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "CheckerLocker.h"
#include "ColliderComponent.h"
#include "MouseController.h"
#include "TransformComponent.h"
#include <iostream>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


using namespace std;
void CheckerLocker::init()
{
    collider = &entity->getComponent<ColliderComponent>();

    transform = &entity->getComponent<TransformComponent>();
    mouse = &entity->getComponent<MouseController>();
    position = &entity->getComponent<CheckerLinker>();
   
    for (auto& tile : Game::tiles) {
        if (position->getPiece()->getPosition() == tile->getComponent<TileLinker>().getPos())
        {
            currentTile = tile;
            break;
        }
    }
}

void CheckerLocker::update()
{

    if (!mouse->isMouseDragging)
    {
        lockPiece(currentTile);
    }
  
    if (position->getPiece()->getisKinged())
    {
        if (position->getPiece()->getColor() == 'R')
        {
            entity->getComponent<SpriteComponent>().setTex("assets/checkersPieces/redPieceKing.png");
        }
        else
        {
            entity->getComponent<SpriteComponent>().setTex("assets/checkersPieces/blackPieceKing.png");
        }
    }


}
bool CheckerLocker::checkCollision(Entity* tile)
{

        ColliderComponent* otherCollider = &tile->getComponent<ColliderComponent>();
        if (otherCollider != collider && Collision::AABB(*collider, *otherCollider) && otherCollider->tag != collider->tag)
        {
            return true;
        }

        return false;
        

}

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

void CheckerLocker::lockPiece(Entity *tile)
{
    transform->position.x=tile->getComponent<ColliderComponent>().collider.x + (tile->getComponent<ColliderComponent>().collider.w / 2.0f) - (transform->width / 2.0f);
    transform->position.y = tile->getComponent<ColliderComponent>().collider.y + (tile->getComponent<ColliderComponent>().collider.h / 2.0f) - (transform->height / 2.0f);

}

void CheckerLocker::setCurrentTile(Entity* tile)
{
    currentTile = tile;
}

//void CheckerLocker::moveLogic()
//{
//
//    if (Game::board->getTurn() == 'R')
//    {
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
//    }
//    else
//    {
//        Entity* currChecker = nullptr;
//        Entity* currTile = nullptr;
//        Move move = bot.minimaxStart(*Game::board, 'B', true);
//        cout << move.piece->getPosition() << " to " << move.dest << endl;
//        
//
//        if (move.piece->canCapture)
//        {
//            cout << "test" << endl;
//        }
//        else
//        {
//            for (auto& c : Game::checkersEntities)
//            {
//                //cout << c->getComponent<CheckerLinker>().getPiece()->getPosition() << endl;
//                if (c->getComponent<CheckerLinker>().getPiece()->getPosition() == move.piece->getPosition())
//                {
//                    //cout << "IN HERE" << endl;
//                    currChecker = c;
//                    break;
//                }
//
//            }
//
//            for (auto t : Game::tiles)
//            {
//                if (t->getComponent<TileLinker>().getPos() == move.dest)
//                    currTile = t;
//            }
//
//
//           
//
//            Game::board->swap(move.piece, Game::board->getchecker(move.dest.x, move.dest.y), false);
//
//
//        }
//    }
//}


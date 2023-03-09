#include "LogicComponent.h"

void LogicComponent::init() 
{
	mouse = &entity->getComponent<MouseController>();
}


void LogicComponent::update()
{
    Entity* checker = nullptr;
    if (Game::event.type == SDL_MOUSEMOTION)
    {
        for (auto& ch : Game::checkersEntities)
        {
            if (mouseHovering(ch))
            {
                checker = ch;
                break;
            }
        }

        if(checker)
        {

            Checker* currentPiece = checker->getComponent<CheckerLinker>().getPiece();
            for (auto& tile : Game::tiles)
            {

                if (!currentPiece->canCapture)
                {
                    cout << "CURRENT PIECE: " << checker->getComponent<TransformComponent>().position << endl;
                    if (checker->getComponent<CheckerLocker>().checkCollision(tile))
                    {
                        //    If there's a collision, snap this checker to the other collider's position
                        bool canMove = true;
                        for (auto c : Game::checkersEntities)
                        {
                            if (c->getComponent<CheckerLinker>().getPiece()->canCapture && c->getComponent<CheckerLinker>().getPiece()->getColor() == currentPiece->getColor())
                            {
                                canMove = false;
                                break;
                            }
                        }
                        if (currentPiece->getColor() == Game::board->getTurn() && currentPiece->moves.find(tile->getComponent<TileLinker>().getPos()) != currentPiece->moves.end() && canMove || tile->getComponent<TileLinker>().getPos() == currentPiece->getPosition())
                        {
                            checker->getComponent<CheckerLocker>().setCurrentTile(tile);

                            {
                                if (tile->getComponent<TileLinker>().getPos() != currentPiece->getPosition())
                                    swapPiece(tile, currentPiece);
                            }
                            //collisionDetected = true;
                            break;
                        }
                    }
                }
                else
                {

                    bool correctPos = false;
                    int calcx;
                    int calcy;
                    for (auto& dest : currentPiece->moves)
                    {
                        calcx = dest.x - currentPiece->getPosition().x;
                        calcy = dest.y - currentPiece->getPosition().y;

                        if (tile->getComponent<TileLinker>().getPos().x == dest.x + calcx && tile->getComponent<TileLinker>().getPos().y == dest.y + calcy)
                        {
                            correctPos = true;
                            break;
                        }
                    }

                    if (correctPos)
                    {

                        if (checker->getComponent<CheckerLocker>().checkCollision(tile))
                        {
                            checker->getComponent<CheckerLocker>().setCurrentTile(tile);

                            for (auto& c : Game::checkersEntities)
                            {

                                if ((c->getComponent<CheckerLinker>().getPiece()->getPosition().x == (tile->getComponent<TileLinker>().getPos().x - calcx)) && (c->getComponent<CheckerLinker>().getPiece()->getPosition().y == (tile->getComponent<TileLinker>().getPos().y - calcy)))
                                {

                                    capturePiece(currentPiece, c);
                                    break;
                                }
                            }
                            //collisionDetected = true;
                            break;
                        }
                    }




                }

                //if (!collisionDetected)
                //{
                //    lockPiece(currentTile);
                //}
            }
        }



    }
}

void LogicComponent::capturePiece(Checker* checker1, Entity* checker2)
{
    checker2->getComponent<SpriteComponent>().destroyTex();
    Game::board->capture(checker1, checker2->getComponent<CheckerLinker>().getPiece());
    Game::board->allowedMoves(Game::board->getInstances('B'));
    Game::board->allowedMoves(Game::board->getInstances('R'));
}

void LogicComponent::swapPiece(Entity* tile, Checker* checker)
{

    Game::board->swap(checker, Game::board->getchecker(tile->getComponent<TileLinker>().getPos().x, tile->getComponent<TileLinker>().getPos().y), false);

    Game::board->allowedMoves(Game::board->getInstances('B'));
    Game::board->allowedMoves(Game::board->getInstances('R'));
}

bool LogicComponent::mouseHovering(Entity* component)
{

    int mouseX = Game::event.motion.x;
    int mouseY = Game::event.motion.y;
    int componentX = static_cast<int>(component->getComponent<TransformComponent>().position.x);
    int componentY = static_cast<int>(component->getComponent<TransformComponent>().position.y);
    int componentWidth = component->getComponent<TransformComponent>().width;
    int componentHeight = component->getComponent<TransformComponent>().height;

    return (mouseX >= componentX && mouseX < componentX + componentWidth &&
        mouseY >= componentY && mouseY < componentY + componentHeight);
}
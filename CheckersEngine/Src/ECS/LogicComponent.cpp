#include "LogicComponent.h"
#include <chrono>
#include <thread>
void LogicComponent::init() 
{
	mouse = &entity->getComponent<MouseController>();
}


void LogicComponent::update()
{

    if(Game::board->getTurn() == 'R')
    {
        cout << "Player Move" << endl;
        playerMove();

    } 
    else
    {
        cout << "BOT MOVE" << endl;
        botMove();
        
    }
}

void LogicComponent::capturePiece(Checker* checker1, Entity* checker2)
{
    Game::board->capture(checker1, checker2->getComponent<CheckerLinker>().getPiece());
    Game::board->allowedMoves(Game::board->getInstances('B'));
    Game::board->allowedMoves(Game::board->getInstances('R'));
    auto it = std::find(Game::checkersEntities.begin(), Game::checkersEntities.end(), checker2);
    if (it != Game::checkersEntities.end())
    {
        Game::checkersEntities.erase(it);
    }
    checker2->destroy();

    

}

void LogicComponent::swapPiece(Entity* tile, Checker* checker)
{
    cout << "Before: " << checker->getPosition() << endl;
    Game::board->swap(checker, Game::board->getchecker(tile->getComponent<TileLinker>().getPos().x, tile->getComponent<TileLinker>().getPos().y), false);
    cout << "After: " << checker->getPosition() << endl;
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

void LogicComponent::playerMove()
{
    Entity* checker = nullptr;
    if (Game::event.type == SDL_MOUSEBUTTONUP)
    {
        for (auto& ch : Game::checkersEntities)
        {
            if (mouseHovering(ch))
            {
                checker = ch;
                break;
            }
        }
        
        if (checker)
        {

            Checker* currentPiece = checker->getComponent<CheckerLinker>().getPiece();
            cout << "CHECKER POSITION: " << currentPiece->getPosition() << endl;
            cout << "Allowed Moves: ";
            for (auto& m : currentPiece->moves)
            {
                cout << m << " ";
            }
            cout << endl;

            for (auto& tile : Game::tiles)
            {

                if (!currentPiece->canCapture)
                {
                    //cout << "CURRENT PIECE: " << checker->getComponent<TransformComponent>().position << endl;
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
                            checker->getComponent<CheckerLocker>().update();
                            {
                                if (tile->getComponent<TileLinker>().getPos() != currentPiece->getPosition())
                                    swapPiece(tile, currentPiece);
                                
                            }
                            //collisionDetected = true;
                            break;
                        }
                    }
                }
                else if (currentPiece->canCapture && currentPiece->getColor() == Game::board->getTurn())
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
                                cout << c->getComponent<CheckerLinker>().getPiece()->getColor() << ": " << c->getComponent<CheckerLinker>().getPiece()->getPosition() << endl;
                                if ((c->getComponent<CheckerLinker>().getPiece()->getPosition().x == (tile->getComponent<TileLinker>().getPos().x - calcx)) && (c->getComponent<CheckerLinker>().getPiece()->getPosition().y == (tile->getComponent<TileLinker>().getPos().y - calcy)))
                                {
                                    cout << "Capturing: " << c->getComponent<CheckerLinker>().getPiece()->getPosition() << endl;
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

void LogicComponent::botMove()
{
    
    Entity* currChecker = nullptr;
    Entity* currTile = nullptr;
    Entity* capturedChecker = nullptr;
    Move move = bot.minimaxStart(*Game::board, 'B', true);
    cout << move.piece->getPosition() << " to " << move.dest << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));

    if (move.piece->canCapture)
    {
        
        for (auto& c : Game::checkersEntities)
        {
            cout << c->getComponent<CheckerLinker>().getPiece()->getPosition() << " vs " << move.piece->getPosition();
            if (c->getComponent<CheckerLinker>().getPiece()->getPosition() == move.piece->getPosition())
            {
                cout << "IN HERE" << endl;
                currChecker = c;

            }

            if (c->getComponent<CheckerLinker>().getPiece()->getPosition().x == move.dest.x && c->getComponent<CheckerLinker>().getPiece()->getPosition().y == move.dest.y)
            {
                capturedChecker = c;
            }

        }
        bool correctPos = false;
        int calcx = move.dest.x - move.piece->getPosition().x;
        int calcy = move.dest.y - move.piece->getPosition().y;

        for (auto t : Game::tiles)
        {
            if (t->getComponent<TileLinker>().getPos().x == move.dest.x + calcx && t->getComponent<TileLinker>().getPos().y == move.dest.y + calcy)
                currTile = t;
        }

        currChecker->getComponent<CheckerLocker>().setCurrentTile(currTile);
        capturePiece(currChecker->getComponent<CheckerLinker>().getPiece(), capturedChecker);


    }
    else
    {
        for (auto& c : Game::checkersEntities)
        {
            cout << c->getComponent<CheckerLinker>().getPiece()->getPosition() << " vs " << move.piece->getPosition() << endl;
            if (c->getComponent<CheckerLinker>().getPiece()->getPosition() == move.piece->getPosition())
            {
                cout << "IN HERE" << endl;
                currChecker = c;
                break;
            }

        }


        for (auto t : Game::tiles)
        {
            if (t->getComponent<TileLinker>().getPos() == move.dest)
                currTile = t;
        }

        currChecker->getComponent<CheckerLocker>().setCurrentTile(currTile);
        swapPiece(currTile, currChecker->getComponent<CheckerLinker>().getPiece());

    }
}
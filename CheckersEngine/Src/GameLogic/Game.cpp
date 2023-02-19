#include "Game.h"
#include "Board.h"

using namespace std;

Game::Game(){// constructor builds the player
    player.setColor('R');
    bot.setColor('B');

    currPlayer = 'R';
    

}

void Game::changeTurns(){// changes turns by switching the current player
    if(currPlayer == 'R'){
        currPlayer = 'B';
    } else{
        currPlayer = 'R';
    }
}

int Game::update(){// checks if there is a winner at the end of each turn
 
    vector<Checker*> blackPieces = board->getInstances('B');
    vector<Checker*> redPieces = board->getInstances('R');

    int numBlack = blackPieces.size();
    int numRed = redPieces.size();

    if(numBlack == 0){
        cout << "PLAYER 1 WINS" << endl;
        return 0;
    } else if (numRed == 0){
        cout << "THE AI WINS" << endl;
        return 0;
    }
    return 1;
}



void Game::Play(){
    cout << "Address in main: " << board << endl;
    do{
        board->Display();
 
        cout << "Num Black: " << board->getInstances('B').size() << endl;
        cout << "Num Red: " << board->getInstances('R').size() << endl;

        cout << currPlayer << "'s turn" << endl;

        

        if(currPlayer == 'R')
            player.makeMove(board);
        else
            bot.makeMove(board);

        changeTurns();

    }while(update() != 0);
}
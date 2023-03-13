#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Board.h"
#include <iostream>
#include <string>
#include "..\TextureManager.h"
#include "..\Game.h"
using namespace std;

Board::Board(Board &b){
    ROWS = 8;
        checkers = new Checker**[ROWS];  

    for(int i = 0; i < ROWS; i++){
        //Declare a memory block of size COLS (n since a checker board is square)
        checkers[i] = new Checker*[ROWS];
    }

        for(int i = 0;i < ROWS; i++){   // follows the rows
        for(int j = 0; j < ROWS; j++){
            checkers[i][j] = new Checker(i,j, b.getchecker(i,j)->getColor());
        }
    }



    numBoards+=1;
    boardNum = numBoards;
}

Board::Board(int n){
    numBoards = 1;
    boardNum = 1;

    ROWS = n;
    int COLS = n;
    checkers = new Checker**[ROWS];  

    for(int i = 0; i < ROWS; i++){
        //Declare a memory block of size COLS (n since a checker board is square)
        checkers[i] = new Checker*[COLS];
    }
    cout << "NEW BOARD CREATED" << endl;
    int x = 0;
    for(int i = 0;i < ROWS; i++){   // follows the rows
        for(int j = 0; j < ROWS; j++){  //follows the columns
            if(i < 3){                  // creating the black checkers
            if(i%2 == 0){
                if(j% 2 == 0){
                    checkers[i][j] = new Checker(i,j,'B');
                    Game::AddChecker(0, 172 + (j * 50), 105 + (i*59), x++, checkers[i][j]);
                } else{
                    checkers[i][j] = new Checker(i,j, '0');
                }
            } else{
                if(j % 2 == 1){
                    checkers[i][j] = new Checker(i,j,'B');
                    Game::AddChecker(0, (-63 * (i%2)) + 228 + (j * 50), 105 + (i*59), x++, checkers[i][j]);
                } else{
                    checkers[i][j] = new Checker(i,j,'0');
                }
            }
            } else if(i > 4){
           if(i%2 == 0){
                if(j% 2 == 0){
                    checkers[i][j] = new Checker(i,j,'R');
                    Game::AddChecker(1, 172 + (j * 55), 325 + ((i-4) * 59), x++, checkers[i][j]);
                } else{
                    checkers[i][j] = new Checker(i,j,'0');
                    
                }
            } else{
                if(j % 2 == 1){
                    checkers[i][j] = new Checker(i,j,'R');                                                                                                                                                                                 
                    Game::AddChecker(1, (-63 * (i % 2)) + 228 + (j * 55), 325 + ((i-4) * 59), x++, checkers[i][j]);
                } else{
                   checkers[i][j] = new Checker(i,j, '0');
                }
            }
            } else{
                checkers[i][j] = new Checker(i,j, '0');
            }

            }
            
        }

        
}



// Board *Board::copy(){
//     Board *b = new Board();

//     for(int i = 0;i < ROWS; i++){   // follows the rows
//         for(int j = 0; j < ROWS; j++){
//             b->checkers[i][j] = new Checker(i,j, checkers[i][j]->getColor());
//         }
//     }

//     return b;

// }

Board::~Board(){
      for(int i=0;i<ROWS;i++)    //To delete the inner arrays
                delete [] checkers[i];   

      delete [] checkers;              //To delete the outer array
                              //which contained the pointers
                              //of all the inner arrays
      cout << "stuff was deleted" << endl;

}

void Board::Display(){
 cout << "==================================================================================\n\n\n\n";
    cout << "       0         1         2         3         4         5         6         7     \n";
    cout << "  _________________________________________________________________________________\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "0 |    " << *checkers[0][0] << "    |    " << *checkers[0][1] << "    |    " << *checkers[0][2] << "    |    "  << *checkers[0][3] << "    |    " << *checkers[0][4] << "    |    " << *checkers[0][5] << "    |    " << *checkers[0][6] << "    |    " << *checkers[0][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "1 |    " << *checkers[1][0] << "    |    " << *checkers[1][1] << "    |    " << *checkers[1][2] << "    |    "  << *checkers[1][3] << "    |    " << *checkers[1][4] << "    |    " << *checkers[1][5] << "    |    " << *checkers[1][6] << "    |    " << *checkers[1][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "2 |    " << *checkers[2][0] << "    |    " << *checkers[2][1] << "    |    " << *checkers[2][2] << "    |    "  << *checkers[2][3] << "    |    " << *checkers[2][4] << "    |    " << *checkers[2][5] << "    |    " << *checkers[2][6] << "    |    " << *checkers[2][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "3 |    " << *checkers[3][0] << "    |    " << *checkers[3][1] << "    |    " << *checkers[3][2] << "    |    "  << *checkers[3][3] << "    |    " << *checkers[3][4] << "    |    " << *checkers[3][5] << "    |    " << *checkers[3][6] << "    |    " << *checkers[3][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "4 |    " << *checkers[4][0] << "    |    " << *checkers[4][1] << "    |    " << *checkers[4][2] << "    |    "  << *checkers[4][3] << "    |    " << *checkers[4][4] << "    |    " << *checkers[4][5] << "    |    " << *checkers[4][6] << "    |    " << *checkers[4][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "5 |    " << *checkers[5][0] << "    |    " << *checkers[5][1] << "    |    " << *checkers[5][2] << "    |    "  << *checkers[5][3] << "    |    " << *checkers[5][4] << "    |    " << *checkers[5][5] << "    |    " << *checkers[5][6] << "    |    " << *checkers[5][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "6 |    " << *checkers[6][0] << "    |    " << *checkers[6][1] << "    |    " << *checkers[6][2] << "    |    "  << *checkers[6][3] << "    |    " << *checkers[6][4] << "    |    " << *checkers[6][5] << "    |    " << *checkers[6][6] << "    |    " << *checkers[6][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "7 |    " << *checkers[7][0] << "    |    " << *checkers[7][1] << "    |    " << *checkers[7][2] << "    |    "  << *checkers[7][3] << "    |    " << *checkers[7][4] << "    |    " << *checkers[7][5] << "    |    " << *checkers[7][6] << "    |    " << *checkers[7][7] << "    |\n";
    cout << "  |         |         |         |         |         |         |         |         |\n";
    cout << "  |_________|_________|_________|_________|_________|_________|_________|_________|\n";
}



Checker *Board::getchecker(int x, int y){
    if(x < 8 && x >=0 && y < 8 && y >=0)
        return checkers[x][y];
    else
        return NULL;
}



void Board::swap(Checker *check1, Checker *check2, bool doubleJump){
    // cout << "Check 1 old position: " << check1->getPosition() << endl;
    // cout << "Check 2 old position: " << check2->getPosition() << endl;
    // cout << "SWAP DONE IN BOARD #" << boardNum << endl;

    // string desc = "(" + to_string(check1->getPosition().x) + "," + to_string(check1->getPosition().y) + ") to (" + to_string(check2->getPosition().x) + "," + to_string(check2->getPosition().y) + ")";
    // check1->descriptions.push(desc);
   
    if(check1->getPosition() == check2->getPosition()){
        cout << "We have a problem in board #" << boardNum << endl;
        exit(0);
    }


    checkers[check1->getPosition().x][check1->getPosition().y] = check2;
    checkers[check2->getPosition().x][check2->getPosition().y] = check1;
    

    coord temp = check1->getPosition();
    check1->changePosition(check2->getPosition());
    check2->changePosition(temp);
    check1->numMoves++;
    // check1->totalMoves++;

    // cout << "Check 1 new position: " << check1->getPosition() << endl;
    // cout << "Check 2 new position: " << check2->getPosition() << endl;

    if(!doubleJump){
        changeTurn();
    }
    else if(!check1->canCapture){
        changeTurn();
    }
    cout << "Current Turn: " << currentTurn << endl;
}

 vector<Checker*> Board::getInstances(char color){   // returns vectors of instances of color

    vector<Checker*> instances;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(checkers[i][j]->getColor() == color){
                instances.push_back(checkers[i][j]);
            }
        
    }
    }

    return instances;
    
 }

bool Board::isAllowed(Checker *checker){
    //Creating pointers to checker pieces that are in the reach of the checker piece we want to test
    Checker *checkerP = getchecker(checker->getPosition().x + checker->direction, checker->getPosition().y + 1);
    Checker *checkerM = getchecker(checker->getPosition().x + checker->direction, checker->getPosition().y -1);
    checker->moves.clear();
    checker->canCapture = false;
   

    bool canMove = false;

    if(checkerP){
        //If the pointer points to a zero, then there is an open spaxe
        if(checkerP->getColor() != checker->getColor() && checkerP->getColor() != '0' ){
            // We need to check if the space after that is open
            Checker *checkp2 = getchecker(checkerP->getPosition().x + checker->direction,checkerP->getPosition().y + 1);
            // if checkerp2 is in bounds
            if(checkp2){
                //if checkerp2 is open
                if(checkp2->getColor() == '0'){
                    checker->canCapture = true;
                    checker->addMove(checkerP->getPosition());
                    canMove = true;
                }
            }
        }

        if(!checker->canCapture){
            if(checkerP->getColor() == '0'){
                checker->addMove(checkerP->getPosition());
                canMove = true;
                //If the pointer points to something that is not a zero, and it is the opposite color
            } 
        }
    }

    if(checkerM){
        if(checkerM->getColor() != checker->getColor() && checkerM->getColor() != '0'){
            Checker *checkm2 = getchecker(checkerM->getPosition().x + checker->direction, checkerM->getPosition().y -1);
            if(checkm2){
                if(checkm2->getColor() == '0'){
                    if(!checker->canCapture)
                        checker->moves.clear();
                    checker->canCapture = true;
                    checker->addMove(checkerM->getPosition());
                    canMove = true;
                }
            }

        }

        if(!checker->canCapture){
            if(checkerM->getColor() == '0'){
                    checker->addMove(checkerM->getPosition());
                    canMove = true;
            }
        }
    }
    



    if(checker->getisKinged()){
        checkerP = getchecker(checker->getPosition().x - checker->direction, checker->getPosition().y + 1);
        checkerM = getchecker(checker->getPosition().x - checker->direction, checker->getPosition().y -1);


    if(checkerP){
        //If the pointer points to a zero, then there is an open spaxe
        if(checkerP->getColor() != checker->getColor() && checkerP->getColor() != '0' ){
            // We need to check if the space after that is open
            Checker *checkp2 = getchecker(checkerP->getPosition().x - checker->direction,checkerP->getPosition().y + 1);
            // if checkerp2 is in bounds
            if(checkp2){
                //if checkerp2 is open
                if(checkp2->getColor() == '0'){
                    if(!checker->canCapture)
                        checker->moves.clear();
                    checker->canCapture = true;
                    checker->addMove(checkerP->getPosition());
                    canMove = true;
                }
            }
        }

        if(!checker->canCapture){
            if(checkerP->getColor() == '0'){
                checker->addMove(checkerP->getPosition());
                canMove = true;
                //If the pointer points to something that is not a zero, and it is the opposite color
            } 
        }
    }

    if(checkerM){

        if(checkerM->getColor() != checker->getColor() && checkerM->getColor() != '0'){
            Checker *checkm2 = getchecker(checkerM->getPosition().x - checker->direction, checkerM->getPosition().y -1);
            if(checkm2){
                if(checkm2->getColor() == '0'){
                    if(!checker->canCapture)
                        checker->moves.clear();
                    checker->canCapture = true;
                    checker->addMove(checkerM->getPosition());
                    canMove = true;
                }
            }

        }

        if(!checker->canCapture){
            if(checkerM->getColor() == '0'){
                    checker->addMove(checkerM->getPosition());
                    canMove = true;
            }
        }


        }
        
    }
    


    return canMove;


}


vector<Checker*> Board::allowedMoves(vector<Checker*> instances){
    vector<Checker*> allowed;
    
    for(auto x: instances){
        if(isAllowed(x)){
            allowed.push_back(x);
        }
    }

    return allowed;
}

void Board::capture(Checker *check1, Checker *check2){
    // check1->numCaptured++;
    // currentPlayer->numCaptured +=1;
    if(boardNum == 1)
        cout << "Captured!" << endl;
    check2->change('0');
    int calcx = check2->getPosition().x - check1->getPosition().x;
    int calcy = check2->getPosition().y - check1->getPosition().y;
    bool doubleJump = false;
    if(check1->canCapture){
        doubleJump = true;
    }

    swap(check1, getchecker(check2->getPosition().x + calcx, check2->getPosition().y + calcy), doubleJump);
    // check1->canCapture = false;

    // if(isAllowed(check1)){
    //     if(check1->canCapture){
    //         set<coord>::iterator it; 

    //         int i = 1;
    //         for(it = check1->moves.begin(); it != check1->moves.end(); it++){
    //             cout << i << ". " << *it << endl;
    //             i++;
    //         }

    //         int choice;
    //         do{
    //         cout << "Choose a move" << endl;
    //         cin >> choice;
    //         }while(choice <= 0 || choice > i-1);
    //         it = check1->moves.begin();
    //         for(int i = 0; i < choice-1; i++){
    //             it++;
    //         }

    //         swap(check1, getchecker(it->x, it->y));
    //         cout << "Double jump" << endl;
    //     }
    // }
    // scoreBoard[currentPlayer]++;
}

void Board::changeTurn(){
    if(currentTurn == 'B'){
            currentTurn = 'R';
        }
    else{
        currentTurn = 'B';
    }
}
#include <iostream>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

#include <list>
#include "Checker.h"
#include <algorithm>
#include <iterator>
#include <stack>
#include <queue>
// #include "move.h"

class Board{
    private:
    int ROWS;
    Checker ***checkers; //Handles the 2D array dynamically
    char currentTurn = 'B';    


    public:
        Board(Board &b);
        Board(int n);//constructor
        inline static int numBoards = 1;
        int boardNum;

        ~Board();//destructor
        // Board *copy();
        void Display();                             //displays the checkerboard
        Checker *getchecker(int x, int y);          //returns a checker given coordiantes
        list<Checker*> listCheckers;                // checkerboard in 1D list
        vector<Checker*> getInstances(char color);    // returns vectors of instances of color
        bool isAllowed(Checker *checker);           // checks if a piece is allowed to move
        vector<Checker*> allowedMoves(vector<Checker*> instances); // returns a list of checkers that can move
        void swap(Checker *check1, Checker *check2);            // moves a checkerpiece in given direction
        void capture(Checker *check1, Checker *check2);
        char getTurn(){return currentTurn;};
};


#endif /* BOARD_H */
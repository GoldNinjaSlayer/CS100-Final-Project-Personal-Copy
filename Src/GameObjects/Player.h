#include <iostream>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include "Checker.h"
#include <iterator>
// #include "Player.h"
#include "Board.h"
#include <ctime>




struct Move
{
    Checker *piece;
    coord dest;
};

struct tree_node{
    double heuristic;
    Move move;
    vector<tree_node> children;
};


class Player{
    protected:
    char color;
    int numCaptured;
        Checker *choosePiece(vector<Checker*> s);
    coord chooseDestination(Checker* piece);
    // Side side;
    public:
    void setColor(char);
    
    virtual void makeMove(Board *b);
    // void captured(Checker *check1, Checker *check2, Board *board);
    char getColor();

};

class AI : public Player{
    private:
        int depth;
    public:
        AI() : Player(){
            depth = 5;
        }
        // void capture(Checker *check1, Checker *check2, Board board);
        void makeMove(Board *b);
        Move minimaxStart(Board b, char col, bool maximizing);
        double minimax(Board b, char col, bool maximizing, int depth, int alpha, int beta);
        double getHeuristic(Board board);
        char switchColor(char col);
        vector<Move> genMoveVec(vector<Checker*> allowed);
};


#endif /* Player_H */

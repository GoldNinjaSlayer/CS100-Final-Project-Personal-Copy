#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

#ifndef CHECKER_H
#define CHECKER_H

struct coord{
    int x;
    int y;

    friend ostream& operator<<(ostream& os, const coord& pos){
        os << '(' << pos.x << ',' << pos.y << ')';
        return os;
    }

    friend bool operator==(const coord& lhs, const coord& rhs){
        if(lhs.x == rhs.x && lhs.y == rhs.y)
            return true;
        else
            return false;
    }

    bool operator<(const coord& rhs) const{
        if(x == rhs.x){
            return y < rhs.y;
        } else{
            return x < rhs.x;
        }
    }
};

class Checker{
    private:
        coord pos;  // checkers x,y position
        char color; // checkers color
        bool isKinged;  //holds if checker is kinged

        
        // int direction;
        

    public:
        int direction;  //the direction the piece is moving
        bool canCapture;    //if piece is able to capture another piece
        set<coord> moves;   //list of possible moves for the piece
        stack<string> descriptions; //holds piece move history
        int numMoves;               //counts how many times piece has moved
        int numCaptured;            // counts how many pieces this piece has captured
        char cOrig;                 //holds the original color for stat reaons
        coord pOrig;                //holds original position for stat reasons
        // static int totalMoves;
        Checker(int x, int y, char col);    // constructor initializes position and color
        // Checker(int, int, char);
        friend ostream& operator<<(ostream& os, const Checker& check); // overrides ostream operator to display pieces color
        coord getPosition();    // returns the position as a coord 
        void changePosition(coord); // changes the position once moved
        char getColor();        //returns color
        bool getisKinged();     //returns if piece is kinged or not
        void addMove(coord move);   //adds a move to objects move set
        void change(char col);      //changes 'color' if captured


};


#endif /* CHECKER_H */

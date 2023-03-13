#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Checker.h"

Checker::Checker(int x, int y, char col){
    isKinged = false;
    color = col;
    cOrig = col;
    pos.x = x;
    pos.y = y;
    pOrig = pos;
    canCapture = false;

    if(col == 'B'){
        direction = 1;
    } else{
        direction = -1;
    }
}



ostream& operator<<(ostream& os, const Checker& check){
    os << check.color;
    return os;
}



coord Checker::getPosition(){
    return pos;
}

char Checker::getColor(){
    return color;
}

bool Checker::getisKinged(){
    return isKinged;
}

void Checker::changePosition(coord newPos){
    pos.x = newPos.x;
    pos.y = newPos.y;
    if(!isKinged){
        if (color == 'B'){
            if (pos.x == 7)
                isKinged = true;
        } else if(color == 'R')
            if(pos.x == 0)
                isKinged = true;
    }

    if(color == 'R' && pos.x == 0)
        isKinged = true;
    
    if(color == 'B' && pos.x == 7)
        isKinged = true;
}

void Checker::addMove(coord move){
    // cout << move << " added to" << pos << endl;
 
    moves.insert(move);
}

void Checker::change(char col){
    color = col;
}
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Player.h"
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

void Player::makeMove(Board *b){
    vector<Checker*> allowed = b->allowedMoves(b->getInstances(color));

    vector<Checker*> attackers;

    bool canCapt = false;
    for(auto x: allowed){
            if(x->canCapture){
                canCapt = true;
                attackers.push_back(x);
            }
        }

    vector<Checker*> pieces = canCapt?attackers:allowed;
    //Checker* piece = choosePiece(pieces);
    Checker* piece = pieces[0]; // testing purposes
    cout << "YOU CHOSE " << piece->getPosition() << endl;
    //coord move = chooseDestination(piece);
    coord move = *piece->moves.begin(); // testing purposes
    if(canCapt){
        b->capture(piece, b->getchecker(move.x, move.y));
    } else{
        b->swap(piece, b->getchecker(move.x, move.y), false);
    }

    for(auto x: allowed){
            x->moves.clear();
            x->canCapture = false;
        }
    allowed.clear();


}

void Player::setColor(char col){
    color = col;
     srand(static_cast<unsigned int>(time(0)));
}

char Player::getColor(){
    return color;
}

Checker *Player::choosePiece(vector<Checker*> s){


    int i = 1;
    for(auto x: s){
        cout << i << ". " << x->getPosition() << endl;
        i++;
    }

    int choice;
    do{
    cout << "Choose a piece" << endl;
    cin >> choice;
    choice = int(choice);
    }while(choice <= 0 || choice > i-1);

    return s[choice-1];
}


coord Player::chooseDestination(Checker* piece){
   set<coord>::iterator it; 

    int i = 1;
    for(it = piece->moves.begin(); it != piece->moves.end(); it++){
        cout << i << ". " << *it << endl;
        i++;
    }

    int choice;
    do{
    cout << "Choose a move" << endl;
    cin >> choice;
    }while(choice <= 0 || choice > i-1);
    // coord ans = *next(piece->moves.begin(), choice);
    it = piece->moves.begin();
    for(int i = 0; i < choice-1; i++){
        it++;
    }
   

    return *it;
    
}




char AI::switchColor(char col){
    if(col == 'B')  
        return 'R';
    
    return 'B';
}

void AI::makeMove(Board *b){
    // cout << "IN AI MAKE MOVE" <<endl;
    Move move = minimaxStart(*b, getColor(), true);
    cout << "AI move:" << move.piece->getPosition() << " " << move.dest << endl;
    if(move.piece->canCapture)

        b->capture(move.piece, b->getchecker(move.dest.x, move.dest.y));
    else{
        cout << "swapped for ai" << endl;
        cout << "Address in makemove = " << b << endl;
        b->swap(move.piece,  b->getchecker(move.dest.x, move.dest.y), false);
    }
}

vector<Move> AI::genMoveVec(vector<Checker*> allowed){
    vector<Move>  moveVec;

    for(auto x: allowed){
        for(auto y: x->moves){
            Move move;
            move.piece = x;
            move.dest = y;
            // cout << move.piece->getPosition() << " to " << move.dest << " added" << endl;
            moveVec.push_back(move);

            
        }
    }

    return moveVec;
}

Move AI::minimaxStart(Board b, char col, bool maximizing){
    // cout << "IN MINIMAXSTART" << endl;
    int alpha = -1000;
    int beta = 1000;
    vector<double> heuristics;
    vector<Move> possible_moves;
    vector<Checker*> instances = b.getInstances(col);
    // cout << "MINIMAXSTART GOT INSTANCES" << endl;
    vector<Checker*> allowed = b.allowedMoves(instances);
    // cout << "MINIMAXSTART GOT ALLOWED MOVES" << endl;
 
    vector<Checker*> attackers;

    bool canCapt = false;
    for(auto x: allowed){
            if(x->canCapture){
                canCapt = true;
                attackers.push_back(x);
            }
        }
    // cout <<"CHECKED IF ATTACKERS" << endl; 
    
    if(canCapt){
        possible_moves = genMoveVec(attackers);
    } else{
        possible_moves = genMoveVec(allowed);
    }

    for(auto x: possible_moves){
            Board tempBoard(b);

            Checker *tempCheck = tempBoard.getchecker(x.piece->getPosition().x,x.piece->getPosition().y);
            
            if(x.piece->canCapture){
                tempBoard.capture(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y));

            }
            else{
                tempBoard.swap(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y), false);

                
            }

            heuristics.push_back(minimax(tempBoard, switchColor(col), !maximizing, depth-1, alpha, beta));    



    }


    double max_heuristics = -1000;
    int num_heuristics = heuristics.size();

    for(int i = num_heuristics -1; i>= 0; i--){
        if(heuristics[i] >= max_heuristics){
            max_heuristics = heuristics[i];
        }
    }

    for(int i = 0; i < num_heuristics; i++){
        if(heuristics[i] < max_heuristics){
        heuristics.erase(heuristics.begin() + i);
        possible_moves.erase(possible_moves.begin() + i);
        i--;
        num_heuristics--;
        }
    }

    int num_moves = possible_moves.size();

    Move final_move = possible_moves[rand() % num_moves];

    return final_move;
}

double AI::minimax(Board b, char col, bool maximizing, int depth, int alpha, int beta){

    // cout << "IN MINIMAX" << endl;
    if(depth == 0){
        return getHeuristic(b);
    }
    vector<Move> possible_moves;
    vector<Checker*> instances = b.getInstances(col);
    vector<Checker*> allowed = b.allowedMoves(instances);
    vector<Checker*> attackers;

    bool canCapt = false;
    for(auto x: allowed){
            if(x->canCapture){
                canCapt = true;
                attackers.push_back(x);
            }
        }
    
    if(canCapt){
        possible_moves = genMoveVec(attackers);
    } else{
        possible_moves = genMoveVec(allowed);
    }


    int initial = 0;
    // Board tempBoard;
        if (maximizing) {
        for (auto x: possible_moves) {
            Board tempBoard(b);
            Checker *tempCheck = tempBoard.getchecker(x.piece->getPosition().x,x.piece->getPosition().y);

            if(x.piece->canCapture){

                tempBoard.capture(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y));
                
            }
            else{
                tempBoard.swap(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y), false);

            }

            int result = minimax(tempBoard, switchColor(col), !maximizing, depth - 1, alpha, beta);
            // cout << "After result" << endl;
            initial = max(result, initial);
            alpha = max(initial, alpha);
            if (alpha >= beta) {
                break;
            }   

        }
    } else {
        initial = 1000;
        for (auto x: possible_moves) {
            Board tempBoard(b);

            Checker *tempCheck = tempBoard.getchecker(x.piece->getPosition().x,x.piece->getPosition().y);
            if(x.piece->canCapture){
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                tempBoard.capture(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y));
                // cout << "AI CAPTURE MOVE IN MINIMAX MINIMIZING" << endl;
            }
            else{
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                tempBoard.swap(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y), false);
                // cout << "AI SWAP MOVE IN MINIMAX MINIMIZING" << endl;
                
            }


            int result = minimax(tempBoard, switchColor(col), !maximizing, depth - 1, alpha, beta);
            initial = min(result, initial);
            beta = min(beta, initial);

            
            if (alpha >= beta) {
                break;
            }  
    

        }
    }

    return initial;

}

double AI::getHeuristic(Board board) {
    double king_weight = 1.5;

    vector<Checker*> blackPieces = board.getInstances('B');
    vector<Checker*> redPieces = board.getInstances('R');

    int numBlack = blackPieces.size();
    int numRed = redPieces.size();

    int numBlackKings = 0;
    int numRedKings = 0;
    for(auto x: blackPieces){
        if(x->getisKinged())
            numBlackKings++;
    }

    for(auto x: redPieces){
        if(x->getisKinged())
            numRedKings++;
    }
    


    if (getColor() == 'B') {
        return (king_weight * numBlackKings + numBlack) - (king_weight * numRedKings + numRed);
    }
    return (king_weight * numRedKings + numRed) - (king_weight * numBlackKings + numBlack);
}

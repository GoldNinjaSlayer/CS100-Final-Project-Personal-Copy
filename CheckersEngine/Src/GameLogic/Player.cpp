#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Player.h"

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
    Checker* piece = choosePiece(pieces);
    cout << "YOU CHOSE " << piece->getPosition() << endl;
    coord move = chooseDestination(piece);
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

// void Player::captured(Checker *check1, Checker *check2, Board *board){
//     // check1->numCaptured++;
//     // currentPlayer->numCaptured +=1;
//     cout << "Captured!" << endl;
//     check2->change('0');
//     int calcx = check2->getPosition().x - check1->getPosition().x;
//     int calcy = check2->getPosition().y - check1->getPosition().y;

//     board->swap(check1, board->getchecker(check2->getPosition().x + calcx, check2->getPosition().y + calcy));
//     // scoreBoard[currentPlayer]++;

// }



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

    // cout <<  "POSSIBLE MOVES BEFORE MINIMAX" << endl;

// ;
//     for(vector<Move>::iterator it = possible_moves.begin(); it!=possible_moves.end(); ){
//         if(it->piece->getPosition() == it->dest){
//             it = possible_moves.erase(it);
//         }else{
//             ++it;
//         }
//     }
// 
    // Board tempBoard;
    for(auto x: possible_moves){
            Board tempBoard(b);

            Checker *tempCheck = tempBoard.getchecker(x.piece->getPosition().x,x.piece->getPosition().y);
            
            if(x.piece->canCapture){
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                tempBoard.capture(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y));
                // cout << "AI CAPTURE MOVE IN MINIMAXSTART" << endl;
                
            }
            else{
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                tempBoard.swap(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y), false);
                // cout << "AI SWAP MOVE IN MINIMAXSTART" << endl;
                
            }
            // cout << "TEMP BOARD MINIMAXSTART" << endl;
            // tempBoard.Display();


            // cout << "NUM R: " << b.getInstances('R').size() << endl;
            // cout << "NUM B: " << b.getInstances('B').size() << endl;
            // //checking error
            // if(b.getInstances('B').size() > 12){
            //     cout << "<B start ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     exit(0);
            // }

            // if(b.getInstances('R').size() > 12){
            //     cout << "<R start ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     exit(0);
            // }

            
  

            heuristics.push_back(minimax(tempBoard, switchColor(col), !maximizing, depth-1, alpha, beta));    
            // cout << "PUSHED BACK" << endl;
   


    }



    // cout << "OUT OF MINIMAX LOOP" << endl;

    double max_heuristics = -1000;
    int num_heuristics = heuristics.size();

    for(int i = num_heuristics -1; i>= 0; i--){
        if(heuristics[i] >= max_heuristics){
            max_heuristics = heuristics[i];
        }
    }
    // cout << "CHECKED MAX HEURISTICS" << endl;
    // cout << "POSSIBLE MOVES BEFORE FINAL MOVE BEFORE CLEANING" << endl;
    // for(auto x: possible_moves){
    //     cout << x.piece->getPosition() << " to " << x.dest << endl;
    // }

    // cout << "MOVES SIZE BEFORE " << possible_moves.size() << endl;
    for(int i = 0; i < num_heuristics; i++){
        if(heuristics[i] < max_heuristics){
        heuristics.erase(heuristics.begin() + i);
        possible_moves.erase(possible_moves.begin() + i);
        i--;
        num_heuristics--;
        }
    }
    // cout << "DELETED BAD MOVES" << endl;
    // cout << "MOVES SIZE AFTER " << possible_moves.size() << endl;

    int num_moves = possible_moves.size();
    // cout << "POSSIBLE MOVES BEFORE FINAL MOVE AFTER CLEANING" << endl;
    // for(auto x: possible_moves){
    //     cout << x.piece->getPosition() << " to " << x.dest << endl;
    // }
    Move final_move = possible_moves[rand() % num_moves];
    // cout << "CHOSE FINAL MOVE" << final_move.piece->getPosition() << " to " << final_move.dest << endl;
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
    // cout <<" IN MINIMAX GOT POSSIBLE MOVES" << endl;
    // cout << "CHECKING IF MOVES HAVE RIGHT AMOUNT" << endl;
    // for(auto x: possible_moves){
    //     cout << x.piece->getColor() << ": " << x.piece->getPosition() << "--" << x.dest << endl;
    // }


    int initial = 0;
    // Board tempBoard;
        if (maximizing) {
        for (auto x: possible_moves) {
            Board tempBoard(b);
            Checker *tempCheck = tempBoard.getchecker(x.piece->getPosition().x,x.piece->getPosition().y);

            if(x.piece->canCapture){
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                // cout << "AI CAPTURE MOVE IN MINIMAX MAXIMIZING" << endl;
                tempBoard.capture(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y));
                
            }
            else{
                // cout << x.piece->getColor() << ": " << x.piece->getPosition() << " to " << x.dest << endl;
                tempBoard.swap(tempCheck, tempBoard.getchecker(x.dest.x, x.dest.y), false);
                // cout << "AI SWAP MOVE IN MINIMAX MAXIMIZING" << endl;
            }
            // cout << "TEMP BOARD MINIMAX" << endl;
            //     tempBoard.Display();

            // cout << "NUM R: " << b.getInstances('R').size() << endl;
            // cout << "NUM B: " << b.getInstances('B').size() << endl;
            // //CHECKING ERROR
            // if(b.getInstances('B').size() > 12){
            //     cout << "<B ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     exit(0);
            // }

            // if(b.getInstances('R').size() > 12){
            //     cout << "<R ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     exit(0);
            // }

   

            // cout << "Before result" << endl;
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
            // cout << "TEMP BOARD MINIMAX" << endl;
            // tempBoard.Display();

            // cout << "NUM R: " << b.getInstances('R').size() << endl;
            // cout << "NUM B: " << b.getInstances('B').size() << endl;


            // //CHECKING FOR ERROR
            // if(b.getInstances('B').size() > 12){
            //     cout << "<B ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     // exit(0);
            // }

            // if(b.getInstances('R').size() > 12){
            //     cout << "<R ERROR> MAX PIECE 12. Location: board #" << b.boardNum<< endl;
            //     // exit(0);
            // }


            

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
    // cout << "NUM BLACKS " << numBlack << endl;
    // cout << "NUM RED " << numRed << endl;

    // if(numBlack > 12){
    //     cout << "ERROR> MAX PIECE 12. Location: board #" << board.boardNum<< endl;
    //     exit(0);
    // }

    // if(numRed > 12){
    //     cout << "ERROR> MAX PIECE 12. Location: board #" << board.boardNum<< endl;
    //     exit(0);
    // }

    


    if (getColor() == 'B') {
       // cout << (king_weight * numBlackKings + numBlack) - (king_weight * numRedKings + numRed) << endl;
        return (king_weight * numBlackKings + numBlack) - (king_weight * numRedKings + numRed);
    }
    return (king_weight * numRedKings + numRed) - (king_weight * numBlackKings + numBlack);
}

// void AI::capture(Checker *check1, Checker *check2, Board board){
//     // check1->numCaptured++;
//     // currentPlayer->numCaptured +=1;
//     cout << "Captured!" << endl;
//     check2->change('0');
//     int calcx = check2->getPosition().x - check1->getPosition().x;
//     int calcy = check2->getPosition().y - check1->getPosition().y;

//     board.swap(check1, board.getchecker(check2->getPosition().x + calcx, check2->getPosition().y + calcy));
//     // scoreBoard[currentPlayer]++;

// }
#ifndef case_alphabeta.hpp
#define case_alphabeta.hpp
#include <iostream>
#include <vector>
#include <climits>
#include "ChessBoard.hpp"
#include "ChessPiece.hpp"


ChessBoard* minimax(ChessBoard* current, int maxdepth);
ChessBoard* minAction(ChessBoard* current, int maxdepth, int currdepth);
ChessBoard* maxAction(ChessBoard* current, int maxdepth, int currdepth);
ChessBoard* alphabetaMN(ChessBoard* current, int maxdepth);
ChessBoard* alphabetaMax(ChessBoard* current, int maxdepth, int currdepth, int a, int b);
ChessBoard* alphabetaMin(ChessBoard* current, int maxdepth, int currdepth, int a, int b);



ChessBoard* alphabetaMN(ChessBoard* current, int maxdepth){
    return alphabetaMax(current, maxdepth, 1, 0, 0);
}

ChessBoard* alphabetaMax(ChessBoard* current, int maxdepth,int currdepth, int a, int b){
    vector<ChessBoard*> *legitmoves;
    ChessBoard* alphaboard = NULL;
    ChessBoard* optMove = NULL;
    ChessBoard* genMove = NULL;
    int alpha = a;
    int beta = b;

    if(currdepth >= maxdepth){
        return current;
    }
    else{
        legitmoves = current->allLegalMoves();
        if(legitmoves->size()==0){
            return current;
        }
        for(vector<ChessBoard*>::iterator m = legitmoves->begin(); m != legitmoves->end(); m++){
            genMove = alphabetaMin(*m,maxdepth,currdepth+1,alpha,beta);
            if(optMove == NULL || genMove->evaluate(false) > optMove->evaluate(false)){
                optMove = genMove;
                alphaboard =*m;
                alpha = genMove->evaluate(false);
            }
            if(beta < alpha){
                return alphaboard;
            }
        }
        return alphaboard;
    }

}

ChessBoard* alphabetaMin(ChessBoard* current, int maxdepth, int currdepth, int a, int b){
    vector<ChessBoard*> *legitmoves;
    ChessBoard* betaboard = NULL;
    ChessBoard* optMove = NULL;
    ChessBoard* genMove = NULL;
    int alpha = a;
    int beta = b;

    if(currdepth >= maxdepth){
        return current;
    }
    else{
        legitmoves = current->allLegalMoves();
        if(legitmoves->size()==0){
            return current;
        }
        for(vector<ChessBoard*>::iterator m = legitmoves->begin(); m != legitmoves->end(); m++){
            genMove = alphabetaMax(*m,maxdepth,currdepth+1,alpha,beta);
            if(optMove == NULL || genMove->evaluate(true) > optMove->evaluate(true)){
                optMove = genMove;
                betaboard =*m;
                beta = genMove->evaluate(true);

            }
            if(beta < alpha){
                return betaboard;
            }
        }
        return betaboard;
    }

}






#endif // case_alphabeta

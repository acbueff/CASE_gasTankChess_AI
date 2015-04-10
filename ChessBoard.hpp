#ifndef case_chessboard.hpp
#define case_chessboard.hpp


#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include <sstream>      // std::ostringstream
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <algorithm>

#define KING 0
#define QUEEN 1
#define BISHOP1 2
#define BISHOP2 3
#define KNIGHT1 4
#define KNIGHT2 5

#include "ChessPiece.hpp"

using namespace std;

class ChessBoard{
private:

    ChessPiece *pieceboard[7][8];
    ChessPiece *hpiecetracker[6];
    ChessPiece *cpiecetracker[6];
    string b[7][8];
    bool currplayer;
    int humanpieces[4];
    int computerpieces[4];


public:

    ChessBoard(){
        for(int p = 0; p < 6; p++){
            hpiecetracker[p] = NULL;
            cpiecetracker[p] = NULL;
        }
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 8; j++){
                pieceboard[i][j] = NULL; /**fill*/
            }
        }
    }

    ChessBoard(ChessBoard *plyabove){
        for(int p = 0; p < 6; p++){
            hpiecetracker[p] = NULL;
            cpiecetracker[p] = NULL;
        }
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 8; j++){
                pieceboard[i][j] = NULL; /**fill*/
            }
        }
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 8; j++){
                if(plyabove->getChessPiece(i,j)!=NULL){
                    setChessPiece(i,j, cloneChessPiece(plyabove->getChessPiece(i,j)));
                }
            }
        }
        currplayer = !plyabove->getCurrPlayer();

        humanpieces[king] = plyabove->getPlayerPiece(king, true);
        humanpieces[queen] = plyabove->getPlayerPiece(queen, true);
        humanpieces[bishop] = plyabove->getPlayerPiece(bishop, true);
        humanpieces[knight] = plyabove->getPlayerPiece(knight, true);

        computerpieces[king] = plyabove->getPlayerPiece(king, false);
        computerpieces[queen] = plyabove->getPlayerPiece(queen, false);
        computerpieces[bishop] = plyabove->getPlayerPiece(bishop, false);
        computerpieces[knight] = plyabove->getPlayerPiece(knight, false);

    }

    void setup(){
  /**Human Pieces*/
        //ChessPiece* temp;
        currplayer =false;

        pieceboard[6][4] = new King(true);
        pieceboard[6][4]->setPieceLocation(6,4);
        hpiecetracker[KING] = pieceboard[6][4];
        pieceboard[6][3] = new Queen(true);
        pieceboard[6][3]->setPieceLocation(6,3);
        hpiecetracker[QUEEN] = pieceboard[6][3];
        pieceboard[6][2] = new Bishop(true);
        pieceboard[6][2]->setPieceLocation(6,2);
        hpiecetracker[BISHOP1] = pieceboard[6][2];
        pieceboard[6][5] = new Bishop(true);
        pieceboard[6][5]->setPieceLocation(6,5);
        hpiecetracker[BISHOP2] = pieceboard[6][5];
        pieceboard[5][3] = new Knight(true);
        pieceboard[5][3]->setPieceLocation(5,3);
        hpiecetracker[KNIGHT1] = pieceboard[5][3];
        pieceboard[5][5] = new Knight(true);
        pieceboard[5][5]->setPieceLocation(5,5);
        hpiecetracker[KNIGHT2] = pieceboard[5][5];
/**Computer pieces*/
        pieceboard[0][4] = new King(false);
        pieceboard[0][4]->setPieceLocation(0,4);
        cpiecetracker[KING] = pieceboard[0][4];
        pieceboard[0][3] = new Queen(false);
        pieceboard[0][3]->setPieceLocation(0,3);
        cpiecetracker[QUEEN] = pieceboard[0][3];
        pieceboard[0][2] = new Bishop(false);
        pieceboard[0][2]->setPieceLocation(0,2);
        cpiecetracker[BISHOP1] = pieceboard[0][2];
        pieceboard[0][5] = new Bishop(false);
        pieceboard[0][5]->setPieceLocation(0,5);
        cpiecetracker[BISHOP2] = pieceboard[0][5];
        pieceboard[1][3] = new Knight(false);
        pieceboard[1][3]->setPieceLocation(1,3);
        cpiecetracker[KNIGHT1] = pieceboard[1][3];
        pieceboard[1][5] = new Knight(false);
        pieceboard[1][5]->setPieceLocation(1,5);
        cpiecetracker[KNIGHT2] = pieceboard[1][5];
   /**FILL computer int and and human int arrays*/
        humanpieces[king] = 1;
        humanpieces[queen] = 1;
        humanpieces[bishop] = 2;
        humanpieces[knight] = 2;

        computerpieces[king] = 1;
        computerpieces[queen] = 1;
        computerpieces[bishop] = 2;
        computerpieces[knight] = 2;
    }

    int getPlayerPiece(ChessPieceType ptype, bool pside){
        if(pside == true){
            return humanpieces[ptype];
        }
        else{
            return computerpieces[ptype];
        }
    }

    void setPlayerPiece( ChessPieceType ptype, bool pside,int amount){
        if(pside == true){
            humanpieces[ptype] +=amount;
        }
        else{
            computerpieces[ptype] += amount;
        }
    }

    ChessPiece* getChessPiece(int i, int j){
        return pieceboard[i][j];
    }

    ChessPiece* getCompPieceTracker(int i){
        return cpiecetracker[i];
    }

    ChessPiece* cloneChessPiece(ChessPiece *oldpiece){
        ChessPiece *newPiece;
        bool side = oldpiece->getSide();
        switch (oldpiece->getPieceType()){
            case king:
                newPiece=new King(side);
                newPiece->setGas(oldpiece->getGas());
                if(side){
                    hpiecetracker[KING] = newPiece;
                }
                else{
                    cpiecetracker[KING] = newPiece;
                }
                break;
            case queen:
                newPiece=new Queen(oldpiece->getSide());
                newPiece->setGas(oldpiece->getGas());
                 if(side){
                    hpiecetracker[QUEEN] = newPiece;
                }
                else{
                    cpiecetracker[QUEEN] = newPiece;
                }
                break;
            case bishop:
                newPiece=new Bishop(oldpiece->getSide());
                newPiece->setGas(oldpiece->getGas());
                 if(side){
                     if(hpiecetracker[BISHOP1] == NULL){
                        hpiecetracker[BISHOP1] = newPiece;
                     }
                     else{
                        hpiecetracker[BISHOP2] = newPiece;
                     }
                }
                else{
                    if(cpiecetracker[BISHOP1] == NULL){
                        cpiecetracker[BISHOP1] = newPiece;
                     }
                     else{
                        cpiecetracker[BISHOP2] = newPiece;
                     }
                }
                break;
            case knight:
                newPiece=new Knight(oldpiece->getSide());
                newPiece->setGas(oldpiece->getGas());
                if(side){
                     if(hpiecetracker[KNIGHT1] == NULL){
                        hpiecetracker[KNIGHT1] = newPiece;
                     }
                     else{
                        hpiecetracker[KNIGHT2] = newPiece;
                     }
                }
                else{
                    if(cpiecetracker[KNIGHT1] == NULL){
                        cpiecetracker[KNIGHT1] = newPiece;
                     }
                     else{
                        cpiecetracker[KNIGHT2] = newPiece;
                     }
                }
                break;
            default:
                break;
        }
        return newPiece;
    }

    void setChessPiece(int i, int j, ChessPiece* p){
        pieceboard[i][j] = p;

        if( p != NULL){
           p->setPieceLocation(i,j);
        }

    }

    /**CHANGE THIS*/
    bool getCurrPlayer(){
        return currplayer;
    }

    void setCurrPlayer(bool player){
        currplayer=player;
    }
    void flipCurrPlayer(){
        currplayer=!currplayer;
    }

    int getTotalGas(bool side){
        int total = 0;
        for(int i = 0; i<6;i++){
            if(side && hpiecetracker[i] != NULL){
                total += hpiecetracker[i]->getGas();
            }
            else if(!side && cpiecetracker[i] != NULL){
                total += cpiecetracker[i]->getGas();
            }
        }
        return total;
    }


void printboard(){

    for(int i = 0; i <7; i++){
        for(int j = 0; j <8; j++){

            if(pieceboard[i][j] == NULL){
                b[i][j] = "--";
            }
            else{
                    b[i][j] = pieceboard[i][j]->getID();
            }

        }
    }

    cout << endl;
    cout << "7 " << b[0][0] << " " << b[0][1] << " " << b[0][2] << " " << b[0][3]<< " " << b[0][4] <<  " " << b[0][5] << " " << b[0][6] <<" " <<b[0][7]<< " " << "computer"<< endl;
    cout << "6 " << b[1][0] << " " << b[1][1] << " " << b[1][2] << " " << b[1][3]<< " " << b[1][4] <<  " " << b[1][5] << " " << b[1][6] <<" " <<b[1][7]<< endl;
    cout << "5 " << b[2][0] << " " << b[2][1] << " " << b[2][2] << " " << b[2][3]<< " " << b[2][4] <<  " " << b[2][5] << " " << b[2][6] <<" " <<b[2][7]<< endl;
    cout << "4 " << b[3][0] << " " << b[3][1] << " " << b[3][2] << " " << b[3][3]<< " " << b[3][4] <<  " " << b[3][5] << " " << b[3][6] <<" " <<b[3][7]<< endl;
    cout << "3 " << b[4][0] << " " << b[4][1] << " " << b[4][2] << " " << b[4][3]<< " " << b[4][4] <<  " " << b[4][5] << " " << b[4][6] <<" " <<b[4][7]<< endl;
    cout << "2 " << b[5][0] << " " << b[5][1] << " " << b[5][2] << " " << b[5][3]<< " " << b[5][4] <<  " " << b[5][5] << " " << b[5][6] <<" " <<b[5][7]<< endl;
    cout << "1 " << b[6][0] << " " << b[6][1] << " " << b[6][2] << " " << b[6][3]<< " " << b[6][4] <<  " " << b[6][5] << " " << b[6][6] <<" " <<b[6][7]<< " " << "human" << endl;
    cout << " "<<"-----------------------"<<endl;
    cout << " "<<" A"<<" " << " B" << " " << " C" << " "<<" D" << " " << " E"<< " "<< " F" << " " << " G"<< " "<< " H"<<endl;
}


    int evaluate(bool side){
        int evaluation = 0;
        /**number of pieces evaluation*/
        evaluation += (Knight::eval * getPlayerPiece(knight, side));
        evaluation += (Bishop::eval * getPlayerPiece(bishop, side));
        evaluation += (Queen::eval * getPlayerPiece(queen, side));
        evaluation += (King::eval * getPlayerPiece(king, side));
        evaluation -= (Knight::eval * getPlayerPiece(knight, !side));
        evaluation -= (Bishop::eval * getPlayerPiece(bishop, !side));
        evaluation -= (Queen::eval * getPlayerPiece(queen, !side));
        evaluation -= (King::eval * getPlayerPiece(king, !side));
        //evaluation for gas
        if(getTotalGas(side) == 0){
            evaluation -= 5000;
        }
        if(getTotalGas(!side) == 0){
            evaluation += 5000;
        }

        return evaluation;
    }



    /**UP FOR REMOVAL*/
    /**CONSIDER GAS*/
    ChessBoard* makeMove(int row_start, int col_start, int row_end, int col_end){
        ChessBoard *trialplay = new ChessBoard(this);
        ChessPiece* start = trialplay->getChessPiece(row_start,col_start);
        ChessPiece* ending = trialplay->getChessPiece(row_end,col_end);

        if(start->getGas() != 0){
            trialplay->setChessPiece(row_end, col_end, start);
            trialplay->setChessPiece(row_start, col_start, NULL);

            if(ending == NULL){
                start->deGas();
            }
        }
        else{
            return NULL;
        }
        if(ending != NULL){
            trialplay->setPlayerPiece(ending->getPieceType(),ending->getSide(),-1);
            start->resetGas();
        }
        this->flipCurrPlayer();
        return trialplay;
    }

    ChessBoard* legalMakeMove(int row_start, int col_start, int row_end, int col_end){
        ChessPiece* start = getChessPiece(row_start,col_start);
        ChessPiece* ending = getChessPiece(row_end,col_end);
        /**start postion is empty, not legal move*/
        if(start == NULL){
            return NULL;
        }
        /**end/start position is the same, not legal move*/
        if(row_start == row_end && col_start == col_end){
            return NULL;
        }

        if(ending != NULL && ((ending->getSide() == start->getSide()) && ending->getPieceType() == king)){// &&
            return NULL;
        }
        /**WHOS TURN, see if I don't have to do this*/

        if(getCurrPlayer()!= start->getSide()){
            return NULL;//RETURN NULL IF CURRENT MOVING PIECE IS OUT OF TURN
        }


        /**Legal Moves of Pieces*/
        if(start->getPieceType()==knight){
          /**Knight Moves*/

            if( row_end == row_start-2 || row_end == row_start+2){
                if(col_end == col_start - 1 || col_end == col_start +1){
                    return makeMove(row_start,col_start,row_end,col_end);
                }
            }
            else if(col_end == col_start-2 || col_end == col_start+2){
                if(row_end == row_start - 1 || row_end == row_start+1){
                    return makeMove(row_start,col_start,row_end,col_end);
                }
            }
            else{
                //cout <<"Cannot move knight"<<endl;
                return NULL;
            }
        }
        /**BISHOP*/
        else if(start->getPieceType()==bishop){
             //cout<<"trying bishop move logic"<<endl;
            ChessPiece* temp;
            int dist;
                if(row_end<row_start){//moving forwards..human
                    dist = row_start - row_end;
                }
                else if(row_end>row_start){
                    dist =  row_end - row_start;
                }
                else{//same row is illegal

                    return NULL;
                }
                    if(col_end<col_start && ((col_end + dist) == col_start)
                        && row_end < row_start){//moving lefttop...human
                        for(int r1 = 1; r1 < dist; r1++){
                            //temp = pieceboard[row - r1][column - r1];
                            if(getChessPiece(row_start - r1,col_start-r1) != NULL){//if path not empty
                                        return NULL;
                            }
                        }
                        return makeMove(row_start,col_start,row_end,col_end);/**should only occur if NULL*/
                    }
                    else if(col_end>col_start && (col_end - dist) == col_start
                             && row_end < row_start){//moving to righttop..human
                            for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row - r1][column + r1];
                                if(getChessPiece(row_start - r1,col_start+r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                        return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else if(col_end<col_start && (col_end + dist) == col_start &&
                            row_end > row_start){//moving to leftdown..human
                             for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row + r1][column - r1];
                                if(getChessPiece(row_start + r1,col_start-r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                            return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else if(col_end>col_start && (col_end - dist) == col_start
                             && row_end > row_start){//moving to rightdown..human
                            for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row + r1][column + r1];
                                if(getChessPiece(row_start + r1,col_start+r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                            return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else{ return NULL;}

        }
        else if(start->getPieceType()==queen){
            int dist;
            /**Knight MOVES*/
            if( row_end == row_start-2 || row_end == row_start+2){
                if(col_end == col_start - 1 || col_end == col_start +1){
                    return makeMove(row_start,col_start,row_end,col_end);
                }
            }
            else if(col_end == col_start-2 || col_end == col_start+2){
                if(row_end == row_start - 1 || row_end == row_start+1){
                    return makeMove(row_start,col_start,row_end,col_end);
                }
            }
            /**Bishop Moves*/
                if(row_end<row_start){//moving forwards..human
                    dist = row_start - row_end;
                }
                else if(row_end>row_start){
                    dist =  row_end - row_start;
                }
                else{//same row is illegal
                    //cout << "BISHOP::legalmove:: row = newr-> false"<<endl;
                    return NULL;
                }
                    if(col_end<col_start && ((col_end + dist) == col_start)
                        && row_end < row_start){//moving lefttop...human
                        for(int r1 = 1; r1 < dist; r1++){
                            //temp = pieceboard[row - r1][column - r1];
                            if(getChessPiece(row_start - r1,col_start-r1) != NULL){//if path not empty
                                        return NULL;
                            }
                        }
                        return makeMove(row_start,col_start,row_end,col_end);/**should only occur if NULL*/
                    }
                    else if(col_end>col_start && ((col_end - dist) == col_start)
                             && row_end < row_start){//moving to righttop..human
                            for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row - r1][column + r1];
                                if(getChessPiece(row_start - r1,col_start+r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                        return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else if(col_end<col_start && (col_end + dist) == col_start &&
                            row_end > row_start){//moving to leftdown..human
                             for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row + r1][column - r1];
                                if(getChessPiece(row_start + r1,col_start-r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                            return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else if(col_end>col_start && (col_end - dist) == col_start
                             && row_end > row_start){//moving to rightdown..human
                            for(int r1 = 1; r1 < dist; r1++){
                                //temp = b[row + r1][column + r1];
                                if(getChessPiece(row_start + r1,col_start+r1) != NULL){//if path not empty
                                        return NULL;
                                }
                            }
                            return makeMove(row_start,col_start,row_end,col_end);
                    }
                    else{ return NULL;}
        }
        /**king*/
        else if(start->getPieceType()==king){
                //cout<<"trying king movement logic"<<endl;
            int movelist[9][2];
            int curR = row_start;
            int curC = col_start;
            int inc = 0;
            ChessPiece* temp=NULL;
            /**GET LEGAL MOVES*/
            for(int r = row_start -1; r <= row_start+1; r++){
                for(int c = col_start - 1; c <= col_start+1; c++){
                    if(r>=0 && c>=0){
                        temp = getChessPiece(r,c);
                    }
                        if(r != curR || c != curC){//not at current position of piece
                            movelist[inc][0] = r;
                            movelist[inc][1] = c;
                            inc++;
                        }
                        else{//current position not an option
                            movelist[inc][0] = -1;
                            movelist[inc][1] = -1;
                            inc++;
                        }
                }
            }
        /**check to see if moves are legal*/
            for(int i = 0;i < 9;i++){
                    if((movelist[i][0] == row_end) && (movelist[i][1] == col_end)){
                        return makeMove(row_start,col_start,row_end,col_end);
                        break;

                    }
            }
            return NULL;
        }
        else{
            return NULL;
        }
        return NULL;
  }

  vector<ChessBoard*>* allLegalMoves(){
    vector<ChessBoard*> *legalboards = new vector<ChessBoard*>();
    ChessBoard* demo = NULL;
    bool currside = getCurrPlayer();
    if(isKingDead() || isOutofGas()){
        return legalboards;
    }
    for(int r = 0; r < 7; r++){
        for(int c = 0;c<8;c++){
            if(getChessPiece(r,c)!=NULL && getChessPiece(r,c)->getSide()==currside){
                for(int y = 0;y<7;y++){
                    for(int x =0;x<8;x++){
                        if(r==y&&c==x){
                            continue;
                        }
                        if((demo = legalMakeMove(r,c,y,x)) !=NULL){
                            legalboards->push_back(demo);
                            flipCurrPlayer();
                        }
                    }
                }
            }
        }
    }
    return legalboards;
  }



bool isKingDead(){
    if(humanpieces[king] == 0 || computerpieces[king] == 0){
        return true;
    }
    return false;
}

bool isOutofGas(){
    if(getTotalGas(true) == 0 || getTotalGas(false) == 0){
        return true;
    }
    return false;
}

bool checkGameOver(){
        if(humanpieces[king] == 0 || getTotalGas(true) == 0){
            cout <<"You lost this game. Welcome your new robot overlords human!"<<endl;
            return true;
        }
        else if(computerpieces[king] == 0 || getTotalGas(false) == 0){
            cout <<"Congratulations, you have bested me."<<endl;
            return true;
        }
        else{
            return false;
        }
}
};
#endif // case_pieceboard

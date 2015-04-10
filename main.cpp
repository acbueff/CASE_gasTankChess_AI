#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include <time.h>
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"
#include "AlphaBeta.hpp"

#define KING 0
#define QUEEN 1
#define BISHOP1 2
#define BISHOP2 3
#define KNIGHT1 4
#define KNIGHT2 5

using namespace std;

bool whomoves();//who plays first
bool goodentermove(char cs, int rs, char ce, int re);
int translateRowMove( int pos);
int translateColumnMove(char cs, int pos);
int retranslateRowMove( int pos);
char retranslateColumnMove(char cs, int pos);


bool humanmove = false;//false means comp goes first

ChessPiece * oldpiecetracker[6];
ChessPiece* oldP=NULL;
ChessPiece* newP=NULL;
/**Move Start to End position HUMAN*/
    char column_start;//actual move
    int row_start;//for array
    char column_end;
    int row_end;
    //in translation
    int col_start;
    int col_end;

/**Move Start to End position COMPUTER*/
    char compCol_start=NULL;
    int compRow_start;
    char compCol_end=NULL;
    int compRow_end;
    //int translation
    int c_col_start;
    int c_col_end;

/**Get move*/
void entermove();

int main()
{
    ChessBoard *board = new ChessBoard();
    ChessBoard *trial=NULL;
    for(int p = 0; p < 6; p++){
            oldpiecetracker[p] = NULL;
    }
    cout <<"attempting setup board print."<<endl;


    board->setup();
    board->setCurrPlayer(whomoves());
    //humanmove=whomoves();
    board->printboard();

    while(!board->checkGameOver()){
        /**HUMAN-COMPUTER MOVE*/
        if(board->getCurrPlayer()){
            while(trial == NULL){
                //cout << "Enter move:"<<endl;
                entermove();
                trial = board->legalMakeMove(row_start,col_start,row_end,col_end);/**pass entered moves into b arrary, make equal to trial*/
            }
                *board = *trial;
                board->printboard(); /**print contents of board*/
                trial=NULL;
        }
        else{
            time_t begin = time(NULL); /**track time I assume*/


            /**Collect old Computer pieces*/
            for(int i = 0; i<6;i++){
                oldpiecetracker[i] = board->getCompPieceTracker(i);
            }
            board = alphabetaMN(board,4);
            cout << "time = " << time(NULL) - begin<<endl;

            if(board!=NULL){
                board->printboard();

                /**Detect different locations of pieces*/
                for(int i = 0; i < 6; i++){
                    if(board->getCompPieceTracker(i) !=NULL){
                        oldP = oldpiecetracker[i];
                        newP = board->getCompPieceTracker(i);
                        if((oldP->getPieceRow() != newP->getPieceRow())||
                           (oldP->getPieceColumn() != newP->getPieceColumn())){
                            compRow_start = oldP->getPieceRow();
                            c_col_start = oldP->getPieceColumn();
                            compRow_end = newP->getPieceRow();
                            c_col_end = newP->getPieceColumn();
                        }
                    }
                }

                compRow_start = retranslateRowMove(compRow_start);
                compCol_start = retranslateColumnMove(compCol_start,c_col_start);
                compRow_end = retranslateRowMove(compRow_end);
                compCol_end =retranslateColumnMove(compCol_end,c_col_end);

                cout<<"COMPUTER MOVE start("<<compCol_start<<","<<compRow_start<<")->end("<<compCol_end<<","<<compRow_end<<")"<<endl;
                compRow_start = 8 - compRow_start;
                compRow_end = 8 - compRow_end;
                cout<<"COMPUTER TRANSLATE MOVE start("<<compCol_start<<","<<compRow_start<<")->end("<<compCol_end<<","<<compRow_end%8<<")"<<endl;
            }
            else{
                cout<<"game done" << endl;
                break;
            }
        }

    }


    return 0;
}


bool whomoves(){
    string choice;
    cout << "Human, do you want to move first or second?"<<endl;
    cout << "You must enter 'first' if you intend to make the first move." << endl;
    cin >>choice;
        if(choice.compare("first") == 0 || choice.compare("First") == 0 || choice.compare("FIRST") == 0){
          cout << "You will make the first move, good luck human."<< endl;
          return true;
        }
        else{
            cout << "Human, you will be second!"<<endl;
            return false;
        }
}

void entermove(){
    /**NEED FLAG: detect when successful move was made to break loop*/
    while(true){
        cout << "enter move:  ";
        cin >> column_start;
        cin >> row_start;
        cin >> column_end;
        cin >> row_end;
        if(!cin){
            cout << "Bad value "<<endl;
            cin.clear();
        }
        if(goodentermove(column_start,row_start,column_end,row_end)){
            col_start = translateColumnMove(column_start,col_start);
            col_end = translateColumnMove(column_end,col_end);
            row_start = translateRowMove(row_start);
            row_end = translateRowMove(row_end);

            break;

        }
    }
}


//determines if input is correct
bool goodentermove(char cs, int rs, char ce, int re){
    if(cs == 'A' || cs == 'B' || cs == 'C'||cs == 'D'||cs == 'E'||cs == 'F'||cs == 'G'||cs == 'H' ){
        if(ce == 'A' || ce == 'B' || ce == 'C'||ce == 'D'||ce == 'E'||ce == 'F'||ce == 'G'||ce == 'H' ){
            if(rs >= 1 && rs <= 7 ){
                if(re >= 1 && re <= 7 ){
                    return true;
                }else{return false;}
            }else{return false;}
        }else{ return false;}
    }else{ return false;}
}

//turns input into proper movements in b[i][j]
int translateColumnMove(char cs, int pos){
    switch(cs){
    case 'A':
        pos = 0;
        break;
    case 'B':
        pos = 1;
        break;
    case 'C':
        pos = 2;
        break;
    case 'D':
        pos = 3;
        break;
    case 'E':
        pos = 4;
        break;
    case 'F':
        pos = 5;
        break;
    case 'G':
        pos = 6;
        break;
    case 'H':
        pos = 7;
        break;
    default:
        cout << "incorrect input"<<endl;
    }
    return pos;
}

int translateRowMove( int pos){
    switch(pos){
    case 1:
        pos = 6;
        break;
    case 2:
        pos = 5;
        break;
    case 3:
        pos = 4;
        break;
    case 4:
        pos = 3;
        break;
    case 5:
        pos = 2;
        break;
    case 6:
        pos = 1;
        break;
    case 7:
        pos = 0;
        break;
    default:
        cout << "incorrect input"<<endl;
    }
return pos;
}

//turns input into proper movements in b[i][j]
char retranslateColumnMove(char cs, int pos){
    switch(pos){
    case 0:
        pos = 'A';
        break;
    case 1:
        pos = 'B';
        break;
    case 2:
        pos = 'C';

        break;
    case 3:
        pos = 'D';
        break;
    case 4:
        pos = 'E';
        break;
    case 5:
        pos = 'F';
        break;
    case 6:
        pos = 'G';
        break;
    case 7:
        pos = 'H';
        break;
    default:
        cout << "incorrect input"<<endl;
    }
    return pos;
}

int retranslateRowMove( int pos){
    switch(pos){
    case 6:
        pos = 1;
        break;
    case 5:
        pos = 2;
        break;
    case 4:
        pos = 3;
        break;
    case 3:
        pos = 4;
        break;
    case 2:
        pos = 5;
        break;
    case 1:
        pos = 6;
        break;
    case 0:
        pos = 7;
        break;
    default:
        cout << "incorrect input"<<endl;
    }
return pos;
}



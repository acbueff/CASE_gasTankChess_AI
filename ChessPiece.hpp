#ifndef case_chesspiece.hpp
#define case_chesspiece.hpp

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



#define KNIGHT 0
#define BISHOP 1
#define QUEEN 2
#define KING 3

using namespace std;

enum ChessPieceType{
    knight,bishop,queen,king
};

class ChessPiece{
protected:
    /**piecelocation*/
    int row;
    int column;
    bool side;
    ChessPieceType piecetype;
    int gas = 3;
    string ID = "x3";
public:
    virtual void updateID() = 0;
    int getGas(){
        return gas;
    }
    void deGas(){
        gas--;
        updateID();
    }
    void resetGas(){
        gas =3;
        updateID();
    }
    void setGas(int newgas){
        gas=newgas;
        updateID();
    }
    void setID(string id){
        ID = id;
    }
    string getID(){
        return ID;
    }
    bool getSide(){
        return side;
    }
    ChessPieceType getPieceType(){
        return piecetype;
    }
    void setPieceLocation(int i, int j){
        row = i;
        column = j;
    }
    int getPieceRow(){
        return row;
    }
    int getPieceColumn(){
        return column;
    }

    static const int eval;
};


class King: public ChessPiece{
public:
    King(bool side){
        this->piecetype = king;
        this->side = side;
        if(side == true){
            ID = "k3";
        }
        else{
            ID = "K3";
        }
    }
    static const int eval = 5000; /**MAX VALUE*/
    void printpiece(){
            cout<<ID<<endl;
    }
    void updateID(){
            string gasamount;
            string temp;
            std::ostringstream convert;
            convert << gas;
            gasamount = convert.str();
            if(side == true){//human
                temp = "k" + gasamount;
                setID(temp);
            }
            else{//computer
                temp = "K" + gasamount;
                setID(temp);
            }
    }

};

class Queen: public ChessPiece{
public:
    Queen(bool side){
        this->piecetype = queen;
        this->side = side;
        if(side == true){/**true indicates human*/
            ID = "q3";
        }
        else{
            ID = "Q3";
        }
    }
    static const int eval = 1000;/**MAX VALUE*/
    void updateID(){
            string gasamount;
            string temp;
            std::ostringstream convert;
            convert << gas;
            gasamount = convert.str();
            if(side == true){//human
                temp = "q" + gasamount;
                setID(temp);
            }
            else{//computer
                temp = "Q" + gasamount;
                setID(temp);
            }
    }
};

class Bishop: public ChessPiece{
public:
    Bishop(bool side){
        this->piecetype = bishop;
        this->side = side;
        if(side == true){/**true indicates human*/
            ID = "b3";
        }
        else{
            ID = "B3";
        }
    }
    static const int eval = 400; /**MAX VALUE*/

    void updateID(){
            string gasamount;
            string temp;
            std::ostringstream convert;
            convert << gas;
            gasamount = convert.str();
            if(side == true){//human
                temp = "b" + gasamount;
                setID(temp);
            }
            else{//computer
                temp = "B" + gasamount;
                setID(temp);
            }
    }
};

class Knight: public ChessPiece{
public:
    Knight(bool side){
        this->piecetype = knight;
        this->side = side;
        if(side == true){/**true indicates human*/
            ID = "n3";
        }
        else{
            ID = "N3";
        }
    }
    static const int eval = 350; /**MAX VALUE*/
    void updateID(){
            string gasamount;
            string temp;
            std::ostringstream convert;
            convert << gas;
            gasamount = convert.str();
            if(side == true){//human
                temp = "n" + gasamount;
                setID(temp);
            }
            else{//computer
                temp = "N" + gasamount;
                setID(temp);
            }
    }
};

#endif

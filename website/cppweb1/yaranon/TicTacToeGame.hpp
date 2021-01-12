#ifndef TICTACTOEGAME_HPP
#define TICTACTOEGAME_HPP

#include <iostream>
#include <vector>
#include <string>
#include "GameBoard.hpp"
#include "Piece.hpp"
#include <cmath>

class TicTacToeGame{

public: 
    int turnCount;
    GameBoard gb;
    Piece X , O;

    TicTacToeGame(){
        this->turnCount = 0;
        X = Piece("X");
        O = Piece("O");
    }

    void init(){
        X = Piece("X");
        O = Piece("O");
        gb = GameBoard();
        turnCount = 0;
    }

    nlohmann::json playGame(int position){
        int row;
        nlohmann::json x;
        x["win"] = nullptr;
        if(position < 0 || position > 8){
            x["message"] = "Enter a position within the bounds!";
            return x;
        }
        else if(X.pos[position] == 1 || O.pos[position] == 1){
            x["message"] = "Slot is taken, enter another number: ";
            return x;
        }
        if(turnCount % 2 == 1){
            turnCount++;
            x["turn"] =  X.getName() + "'s turn. Enter a number 0 - 8 to place your piece: \r\n";
        }
        else{
            turnCount++;
            x["turn"] = O.getName() + "'s turn. Enter a number 0 - 8 to place your piece: \r\n";
        }
        if(position <= 2){
               row = 0;
           }
           else if(position <= 5){
               row = 1;
           }
           else{
               row = 2;
           }
        if(turnCount % 2 == 1){
            X.setPos(position);
            gb.boardVect[row][(position % 3) * 2] = X.getName();
            gb.checkFull[position] = 1;
        }
        else{
            O.setPos(position);
            gb.boardVect[row][(position % 3) * 2] = O.getName();
            gb.checkFull[position] = 1;
        }
        x["gb"] = gb.boardVect;
        if(gb.isFull()){
            x["win"] = "TIE!\r\n";
            x["message"] = nullptr;
            return x;
        }
        if(gb.threeInARow(X, O)){
            if(turnCount % 2 == 1){
                x["win"] = (X.getName() + " has WON!");
            }
            else{
                x["win"] = (O.getName() + " has WON!");
            }
            x["message"] = nullptr;
            return x;
        }
        return x;
    }
};
#endif

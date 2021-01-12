#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "Piece.hpp"
#include <vector>
#include <iostream>

class GameBoard{

public:
    std::vector<std::vector<std::string>> boardVect;
    std::vector<int> checkFull;

    //Default constructor
    GameBoard(){
        //Initialize vector which checks if board is FULL
        for(int i = 0; i <= 8; i++){
            this->checkFull.push_back(0); //{0,0,0,0,0,0,0,0,0}
        }
        for(int i = 0; i <= 2; i++){
            std::vector<std::string> tempVect;
            for(int j = 0; j <= 4; j++){
                if(j % 2 == 0){
                    tempVect.push_back("_");
                }
                else{
                    tempVect.push_back("|");
                }
            }
            this->boardVect.push_back(tempVect);
        }
        printGameBoardInit(this->boardVect);
    }

    void printGameBoardInit(std::vector<std::vector<std::string>> boardVect){
        for(int i = 0; i <= 2; i++){
            for(int j = 0; j <= 4; j++){
                std::cout << boardVect[i][j];
            }
           std::cout << "" << std::endl;
        }
    }

    void printGameBoard(Piece X, Piece O){
        for(int i = 0; i <= 2; i++){
            for(int j = 0; j <= 4; j++){
                std::cout << boardVect[i][j];
            }
           std::cout << "" << std::endl;
        }
    }

    bool threeInARow(Piece X, Piece O){
        //UP TO DOWN
        if(X.pos[0] == 1 && X.pos[0] == X.pos[3] && X.pos[0] == X.pos[6]){
            //std::cout << "CHECK 1";
            return true;
        }
        if(X.pos[1] == 1 && X.pos[1] == X.pos[4] && X.pos[1] == X.pos[7]){
            //std::cout << "CHECK 2";
            return true;
        }
        if(X.pos[2] == 1 && X.pos[2] == X.pos[5] && X.pos[2] == X.pos[8]){
            //std::cout << "CHECK 3";
            return true;
        }

        //LEFT TO RIGHT
        if(X.pos[0] == 1 && X.pos[0] == X.pos[1] && X.pos[0] == X.pos[2]){
            //std::cout << "CHECK 4";
            return true;
        }
        if(X.pos[3] == 1 && X.pos[3] == X.pos[4] && X.pos[3] == X.pos[5]){
            //std::cout << "CHECK 5";
            return true;
        }
        if(X.pos[6] == 1 && X.pos[6] == X.pos[7] && X.pos[6] == X.pos[8]){
            //std::cout << "CHECK 6";
            return true;
        }

        //DIAGONAL
        if(X.pos[0] == 1 && X.pos[0] == X.pos[4] && X.pos[0] == X.pos[8]){
            //std::cout << "CHECK 7";
            return true;
        }
        if(X.pos[2] == 1 && X.pos[2] == X.pos[4] && X.pos[2] == X.pos[6]){
            //std::cout << "CHECK 8";
            return true;
        }

        //O

        if(O.pos[0] == 1 && O.pos[0] == O.pos[3] && O.pos[0] == O.pos[6]){
            //std::cout << "CHECK 9";
            return true;
        }
        if(O.pos[1] == 1 && O.pos[1] == O.pos[4] && O.pos[1] == O.pos[7]){
            //std::cout << "CHECK 10";
            return true;
        }
        if(O.pos[2] == 1 && O.pos[2] == O.pos[5] && O.pos[2] == O.pos[8]){
            //std::cout << "CHECK 11";
            return true;
        }

        //LEFT TO RIGHT
        if(O.pos[0] == 1 && O.pos[0] == O.pos[1] && O.pos[0] == O.pos[2]){
            //std::cout << "CHECK 12";
            return true;
        }
        if(O.pos[3] == 1 && O.pos[3] == O.pos[4] && O.pos[3] == O.pos[5]){
            //std::cout << "CHECK 13";
            return true;
        }
        if(O.pos[6] == 1 && O.pos[6] == O.pos[7] && O.pos[6] == O.pos[8]){
            //std::cout << "CHECK 14";
            return true;
        }

        //DIAGONAL
        if(O.pos[0] == 1 && O.pos[0] == O.pos[4] && O.pos[0] == O.pos[8]){
            //std::cout << "CHECK 15";
            return true;
        }
        if(O.pos[2] == 1 && O.pos[2] == O.pos[4] && O.pos[2] == O.pos[6]){
            //std::cout << "CHECK 16";
            return true;
        }
    return false;
    }

    bool isFull(){
        int count = 0;
        for(int i = 0; i <= 8; i++){
            if(this->checkFull[i] != 0){
                count++;
            }
        }
        if(count == 9){
            return true;
        }
    return false;
    }
};

#endif

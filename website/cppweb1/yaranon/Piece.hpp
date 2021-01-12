#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <string>

class Piece{

public:
    std::vector<int> pos; //Vector of 0's and 1's
    std::string name;

    //Default constructor
    Piece(){
        this->name = "";
        for(int i = 0; i < 9; i++){
            this->pos.push_back(0);
        }
    }
    //Constructor with parameters
    Piece(std::string name){
        this->name = name;
        for(int i = 0; i < 9; i++){
            this->pos.push_back(0);
        }
    }
    void setName(std::string name){
        this->name = name;
    }
    std::string getName(){
        return this->name;
    }
    void setPos(int spot){
        this->pos[spot] = 1;
    }
};

#endif

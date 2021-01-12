#ifndef BOARD_H
#define BOARD_H

#include "crow_all.h"
#include <vector>


class Board{

public:
    std::vector<std::string> dashes;
    std::string hangman;

    Board(){
    this->hangman =
         " --------\r\n"
         " |      |\r\n"
         " |\r\n"
         " |\r\n"
         " |\r\n"
         " |\r\n"
        "__|_________\r\n";
    }

    Board(int wordSize){
        this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |\r\n"
        " |\r\n"
        " |\r\n"
        " |\r\n"
        "_|_________\r\n";

        for(int i = 0; i < wordSize; i++)
            this->dashes.push_back("_");
    }

    std::string getState(){
        return this->hangman;
    }

    void addPart(int guesses){
        if(guesses == 5){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |\r\n"
        " |\r\n"
        " |\r\n"
        "_|_________\r\n";
        }
        else if(guesses == 4){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |      |\r\n"
        " |\r\n"
        " |\r\n"
        "_|_________\r\n";
        }
        else if(guesses == 3){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |     /|\r\n"
        " |\r\n"
        " |\r\n"
        "_|_________\r\n";
        }
        else if(guesses == 2){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |     /|\\ \r\n"
        " |\r\n"
        " |\r\n"
        "_|_________\r\n";
        }
        else if(guesses == 1){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |     /|\\ \r\n"
        " |     / \r\n"
        " |\r\n"
        "_|_________\r\n";
        }
        else if(guesses == 0){
            this->hangman =
        " --------\r\n"
        " |      |\r\n"
        " |      O\r\n"
        " |     /|\\ \r\n"
        " |     / \\ \r\n"
        " |\r\n"
        "_|_________\r\n";
        }
    }

    void printState(std::string word, int guesses,  std::vector<std::string> lettersGuessed, int category){
        //std::cout << getState() << std::endl;
        //std::cout << "Category: ";
        if(category == -1){
            //std::cout <<"Custom "<<std::endl;
        }
        else if(category == 1){
            //std::cout << "Animals " << std::endl;
        }
        else if(category == 2){
            //std::cout << "Kitchen " << std::endl;
        }
        else if(category == 0){
            //std::cout << "Random Objects " << std::endl;
        }
        for(int i = 0; i < dashes.size(); i++){
            //std::cout << dashes[i] << " ";
        }
        if(lettersGuessed.size() != 0){
            //std::cout << "\tGuesses left: " << guesses << "\t\tLetters guessed: ";
            for(int i = 0; i < lettersGuessed.size(); i++){
                //std::cout << lettersGuessed[i] << " ";
            }
            //std::cout << "" << std::endl;
        }
        else{
            //std::cout << "\tGuesses left: " << guesses << std::endl; //No one has guessed incorrectly, no need to print out list of guessed words
        }
    }

};
#endif

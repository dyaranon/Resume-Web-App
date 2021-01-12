#ifndef GAME_H
#define GAME_H

#include "crow_all.h"
#include "Board.hpp"
#include "json.h"
#include <iostream>
#include <time.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include <cmath>
#include <unistd.h>

class Game{

public:
    int guesses, category, count, win;
    std::vector<std::string> lettersGuessed;
    std::vector<std::string> pics;
    std::string letter, categoryName;
    Board board;

    Game(){
        this->guesses = 0;
        this->board = Board();
        this->word = "";
    }

    Game(int x){
        this->guesses = 6;
        this->count = 0;
        this->win = 0;
        srand(time(NULL));
        this->category = -1;
        this->word = "";
    }

    std::string getWord(){
        return this->word;
    }

    std::vector<std::string> readWordsFile(std::string fileName){
        std::ifstream file(fileName);
        std::string temp;
        std::vector<std::string> words;
        while(std::getline(file, temp)){
            words.push_back(temp);
        }
        return words;
    }

    std::string fileParse(std::string fileName){
        std::vector<std::string> listOfWords = readWordsFile(fileName);
        std::cout << listOfWords.size() << std::endl;
        int index = rand() % listOfWords.size();
        return listOfWords[index];
    }

    void setWord(std::string word){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        this->word = word;
    }

    void generateWord(){
        this->category = rand() % 3;
        if(this->category == 1){
           this->categoryName = "Animals";
           this->word = fileParse("/usr/src/cppweb1/yaranon/textFiles/Animals.txt");
        }
        else if(this->category == 2){
            this->categoryName = "Kitchen";
            this->word = fileParse("/usr/src/cppweb1/yaranon/textFiles/Foods.txt");
        }
        else{
            this->categoryName = "Random Objects";
            this->word = fileParse("/usr/src/cppweb1/yaranon/textFiles/RandomObjects.txt");
        }
        setWord(this->word);
    }

    bool wordFound(Board board){
        for(int i = 0; i < board.dashes.size(); i++){
            if(board.dashes[i] == "_"){
                return false;
            }
        }
        return true;
    }

    bool lettersDuplicate(std::vector<std::string> lettersGuessed, std::string letter){
        transform(letter.begin(), letter.end(), letter.begin(), ::toupper);
        for (int it = 0; it < lettersGuessed.size(); it++){
            if(lettersGuessed[it] == letter){
                return true;
            }
        }
        return false;
    }

    void init(){
        generateWord();
        this->letter = "";
        this->board = Board(getWord().size() - 1);
        this->guesses = 6;
        this->lettersGuessed.clear();
    }

     nlohmann::json playGame(std::string letter){
        nlohmann::json x;
        this->count = 0;
        x["category"] = this->categoryName;
        if(letter.size() != 1){
            x["err"] = "Please only enter one letter at a time: ";
        }
        else if(lettersDuplicate(this->lettersGuessed, letter)){
            x["err"] = "Letter has already been guessed. Guess again: ";
        }
        else {
            transform(letter.begin(), letter.end(), letter.begin(), ::toupper);
            std::string temp = letter;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            for(int i = 0; i < getWord().size(); i++){
                if(getWord()[i] == letter[0] || getWord()[i] == temp[0]){
                    board.dashes[i] = letter;
                    x["letter"] = letter;
                    this->count++;
                }
            }
            if(this->count != 0){
                board.printState(getWord(), this->guesses, this->lettersGuessed, this->category);
            }
            else{
                this->guesses--;
                x["lettersGuessed"] = letter;
                this->lettersGuessed.push_back(letter);
                board.addPart(this->guesses);
                board.printState(getWord(), this->guesses, this->lettersGuessed, this->category);
            }
        }
        if(this->guesses == 0){
            x["message"] = "YOU LOST! THE WORD WAS " + getWord();
            win = 1;
        }
        x["dashes"] = board.dashes;
        x["guesses"] = this->guesses;
        x["state"] = board.getState();
        if(wordFound(board)){
            x["message"] = "YOU WIN! THE WORD WAS " + getWord();
        }
        if(x["guesses"] < 0){
            x["guesses"] = 0;
        }
       return x;
    }
    
private:
    std::string word;
};
#endif


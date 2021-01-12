#ifndef BATTLE_H
#define BATTLE_H

#include "Warriors.hpp"
#include <vector>
#include <random>
#include <iostream>
#include <vector>
#include "json.h"
#include "crow_all.h"

class Battle{

public:
    int totalTurnCount;
    int whoseTurn;
    int amountAlive;
    int amountOfWarriors;

    Battle(){
        this->totalTurnCount = 1;
        this->whoseTurn = 0;
        this->amountAlive = 0;
        this->amountOfWarriors = 0;
    }

    std::vector<std::string> startFight(std::vector<Warrior> listOfWarriors){
         srand(time(NULL));
         std::vector<std::string> print;
         print.push_back("\r\nBATTLE HAS BEGUN\r\n");
         int opponent_tracker;
         this->amountAlive = listOfWarriors.size();
         this->amountOfWarriors = listOfWarriors.size();
         for(int i = 0; i < this->amountOfWarriors; i++){ //Setting all bonus health
                listOfWarriors[i].bonusHealth = rand() % 11; //Set at beginning of game, different for each warrior
                listOfWarriors[i].setHealth(100 + listOfWarriors[i].bonusHealth);
                print.push_back(listOfWarriors[i].getName());
                print.push_back(" has received ");
                print.push_back(std::to_string(listOfWarriors[i].bonusHealth));
                print.push_back(" bonus health. They now have ");
                print.push_back(std::to_string(listOfWarriors[i].getHealth()));
                print.push_back(" health\r\n");
         }
         while(this->amountAlive > 1){
            opponent_tracker = rand() % this->amountOfWarriors;
            while(opponent_tracker == this->whoseTurn % this->amountOfWarriors || listOfWarriors    [opponent_tracker].getHealth() <= 0){
                opponent_tracker = rand() % this->amountOfWarriors;
            }
            listOfWarriors[this->whoseTurn % this->amountOfWarriors].bonusDamage = rand() % 10 ; //Updated every turn
            listOfWarriors[this->whoseTurn % this->amountOfWarriors].setDamage(5 + listOfWarriors   [this->whoseTurn % this->amountOfWarriors].bonusDamage);

            print.push_back(listOfWarriors[this->whoseTurn % this->amountOfWarriors].getName());
            print.push_back(" deals ");
            print.push_back(std::to_string(listOfWarriors[this->whoseTurn % this->amountOfWarriors ].getDamage()));
            print.push_back(" damage to ");
            print.push_back(listOfWarriors[opponent_tracker].getName());
            print.push_back("\r\n");
            listOfWarriors[opponent_tracker].tookDamage(listOfWarriors[this->whoseTurn % this->amountOfWarriors].getDamage());
            if(listOfWarriors[opponent_tracker].getHealth() <= 0){
                print.push_back(listOfWarriors[opponent_tracker].getName());
                print.push_back(" has been killed by ");
                print.push_back(listOfWarriors[this->whoseTurn %  this->amountOfWarriors].getName());
                print.push_back("\r\n");
                this->amountAlive--;
            }
            this->whoseTurn++;
            while(listOfWarriors[this->whoseTurn % this->amountOfWarriors].getHealth() <= 0){
                this->whoseTurn++;
            }
            this->totalTurnCount++;
        }
        while(listOfWarriors[this->whoseTurn % this->amountOfWarriors].getHealth() <= 0){
                 this->whoseTurn++;
        }
        print.push_back(listOfWarriors[this->whoseTurn % this->amountOfWarriors].getName());
        print.push_back(" HAS WON!\r\n");
        return print;
    }  
};

#endif

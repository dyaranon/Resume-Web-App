#ifndef WARRIORS_H
#define WARRIORS_H

#include <string>
class Warrior{
private:
    int damage;
    int health;

public:
    std::string name;
    int bonusDamage;
    int bonusHealth;
    
    //Default constructor
    Warrior(){
        this->damage = 5;
        this->health = 100;
        this->name = "";
        this->bonusDamage = 0;
        this->bonusHealth = 0;
    }
    //Constructor with parameters
    Warrior(int damage, int health, std::string name){
        this->damage = damage;
        this->health = health;
        this->name = name;
        this->bonusDamage = 0;
        this->bonusHealth = 0;
    }
    int getDamage(){
        return this->damage;
    }
    void setDamage(int newDamage){
        this->damage = newDamage;
    }
    int getHealth(){
        return this->health;
    }
    void setHealth(int newHealth){
        this->health = newHealth;
    }
    void tookDamage(int damage){
        this->health -= damage;
    }
    std::string getName(){
        return this->name;
    }
    void setName(std::string name){
        this->name = name;
    }
    void setAllDetails(int damage, int health, std::string name){
        this->damage = damage;
        this->health = health;
        this->name = name;
    }
    ~Warrior(){
    
}

};

#endif

//
// Created by julie on 13/11/2023.
//

#ifndef CPPDND_CREATURE_H
#define CPPDND_CREATURE_H
#pragma once
#include "stdlib.h"

#include <string>
class Hero;

class Creature {
private:
    int pv;
    int atk;
    int lvl;
    int pvmax;
    std::string name;
public:
    Creature();
    //constructeur
    Creature(int pv, int atk, int lvl, int pvmax, std::string name);
    //methodes
    std::string getStats();
    void attackHero(Hero &h);
    void takeDamage(int dmg);
    int getAtk();
    int getPv();
    int getrandom(int min, int max);
    int getLevel();
    void createCreature(int lvlhero);
    void setAtk(int atk);
    void setPv(int pv);
    void setLevel(int level);
    void setPvmax(int pvmax);
    void setName(std::string name);
    std::string getName();
    void createCustom(int pv, int atk, int lvl, std::string name);
};

#endif //CPPDND_CREATURE_H

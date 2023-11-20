//
// Created by julie on 13/11/2023.
//

#ifndef CPPDND_CREATURE_H
#define CPPDND_CREATURE_H
#pragma once
#include "stdlib.h"

#include <string>
#include "Entity.h"
class Hero;

class Creature : public Entity{
private:

public:
    //constructeur
    Creature();
    Creature(int pv, int atk, int pvmax, int lvl, std::string name);
    //methodes
    std::string getStats();
    void attackHero(Hero &h);
    void takeDamage(int dmg);
    int getrandom(int min, int max);
    void createCreature(int lvlhero);
    void setAtk(int atk);
    void setPv(int pv);
    void setLevel(int level);
    void setPvmax(int pvmax);
    void setName(std::string name);
    void createCustom(int pv, int atk, int lvl, std::string name);
};

#endif //CPPDND_CREATURE_H

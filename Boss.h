//
// Created by julie on 29/11/2023.
//

#ifndef CPPDND_BOSS_H
#define CPPDND_BOSS_H
#include "Entity.h"
#include <String>
#include "stdlib.h"
class Hero;

class Boss : public Entity{
private:
    std::string fastAttack;
    std::string spell;
    std::string heal;
    std::string heavyAttack;
public:
    Boss();
    Boss(int pv, int atk, int pvmax, int lvl, std::string name, std::string fastAttack, std::string spell, std::string heal, std::string heavyAttack);
    std::string getStats();
    void attackHero(Hero &h);
    int getrandom(int min, int max);
};


#endif //CPPDND_BOSS_H

//
// Created by julie on 29/11/2023.
//

#include "Boss.h"
#include <random>

Boss::Boss(){

};

Boss::Boss(int pv, int atk, int pvmax, int lvl, std::string name, std::string fastAttack, std::string spell, std::string heal, std::string heavyAttack) {
    Entity(pv, atk, pvmax, name, lvl);
    this->fastAttack = fastAttack;
    this->spell = spell;
    this->heal = heal;
    this->heavyAttack = heavyAttack;
}

std::string Boss::getStats(){
    return "PV: " + std::to_string(pv) + "/" + std::to_string(pvmax) +" Atk: " + std::to_string(atk) + " Lvl: " + std::to_string(lvl) + "\n";
}

void Boss::attackHero(Hero &h) {
}

int Boss::getrandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
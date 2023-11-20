//
// Created by julie on 13/11/2023.
//

#include "Creature.h"
#include "Hero.h"
#include "stdlib.h"
#include <random>

Creature::Creature() {
}

Creature::Creature(int pv, int atk, int pvmax, int lvl, std::string name) : Entity(pv,  atk,  pvmax, name, lvl){
    Entity (pv, atk, pvmax, name, lvl);
}

std::string Creature::getStats(){
    return "PV: " + std::to_string(pv) + "/" + std::to_string(pvmax) +" Atk: " + std::to_string(atk) + " Lvl: " + std::to_string(lvl) + "\n";
}

void Creature::attackHero(Hero &h){
    printf("Une Creature vous attaque !\n");
    int atk1 = getrandom(0, this->atk) + 2;
    int atk2 = getrandom(0, h.getAtk());
    printf("attaque de la Creature : %d\n", atk1);
    printf("attaque du Hero : %d\n", atk2);
    if (atk1 > atk2){
        if (getrandom(1,15)>14){
            int dmg = atk1;
            printf("La creature inflige un coup critique et vous inflige %d de dommages !\n", dmg);
            h.takeDamage(dmg);
        }
        else{
            int dmg = atk1-atk2;
            printf("La Creature vous inflige %d de dommages !\n", dmg);
            h.takeDamage(dmg);
        }
    }
    else{
        if (getrandom(1,15)>14){
            int dmg = atk2;
            printf("Vous infligez un coup critique et vous infligez %d de dommages !\n", dmg);
            takeDamage(dmg);
        }
        else{
            int dmg = atk2-atk1;
            printf("Vous infligez %d de dommages !\n", dmg);
            takeDamage(dmg);
        }
    }
}

void Creature::takeDamage(int dmg){
    pv -= dmg;
    if (pv <= 0){
        printf("Le/la %s est mort !\n", name.c_str());
    }
}

int Creature::getrandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}


void Creature::setAtk(int atk){
    this->atk = atk;
}

void Creature::setPv(int pv){
    this->pv = pv;
}

void Creature::setLevel(int level){
    this->lvl = level;
}

void Creature::setPvmax(int pvmax){
    this->pvmax = pvmax;
}

void Creature::setName(std::string name){
    this->name = name;
}



void Creature::createCreature(int lvlhero) {
    std::string names[7] = {"Loup","Chimere","Troll","Goblin","Golem","Demon","Dragonneau"};
    int level = getrandom(lvlhero-2, lvlhero+3);
    int pv = getrandom(level*2, level*2+5);
    int atk = getrandom(level+2, level+4);
    int pvmax = pv;
    std::string name = names[getrandom(0,6)];
    this->setPvmax(pvmax);
    this->setPv(pv);
    this->setAtk(atk);
    this->setLevel(level);
    this->setName(name);
}

void Creature::createCustom(int pv, int atk, int lvl, std::string name) {
    this->setPv(pv);
    this->setAtk(atk);
    this->setLevel(lvl);
    this->setName(name);
    this->setPvmax(pv);
}


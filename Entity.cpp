//
// Created by julie on 20/11/2023.
//

#include "Entity.h"

Entity::Entity(int pv, int atk, int pvmax, std::string name, int lvl) {
    this->pv = pv;
    this->atk = atk;
    this->pvmax = pvmax;
    this->name = name;
    this->lvl = lvl;
}

Entity::Entity(){
}

int Entity::getpvmax() {
    return this->pvmax;
}

int Entity::getpv() {
    return this->pv;
}

int Entity::getAtk() {
    return this->atk;
}

std::string Entity::getname() {
    return this->name;
}

int Entity::getlvl() {
    return this->lvl;
}



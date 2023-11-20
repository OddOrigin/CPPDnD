//
// Created by julie on 20/11/2023.
//

#ifndef CPPDND_ENTITY_H
#define CPPDND_ENTITY_H

#include "stdlib.h"
#include <string>


class Entity {
//private:

public:
    Entity(int pv, int atk, int pvmax, std::string name, int lvl);
    Entity();
    int getAtk();
    int getpv();
    int getpvmax();
    int getlvl();
    std::string getname();
protected:

    int pv;
    int atk;
    int pvmax;
    std::string name;
    int lvl;
};

#endif //CPPDND_ENTITY_H

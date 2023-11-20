//
// Created by julie on 17/11/2023.
//

//TODO : RARE ENCOUNTERS, BOSSES, CREATION PERSO, SAVE/LOAD/NEWGAME
//TODO : DUNGEON FOR RARE ENCOUNTER

#ifndef CPPDND_JEU_H
#define CPPDND_JEU_H
#include "Creature.h"
#include "Hero.h"
//#include "Interface.h"

class Jeu {
private:
    //interface
    Hero hero;
    Creature creature;
public:
    Jeu(Hero& h, Creature& c);
    void startGame();
    Hero getHero();
    Creature getCreature();
    //void setInterface(interface);
    void explore();
    void rest();
    void fight();
    void shop();
    void rollQuest();
};

#endif //CPPDND_JEU_H

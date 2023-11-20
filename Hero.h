//
// Created by julie on 13/11/2023.
//

#ifndef CPPDND_HERO_H
#define CPPDND_HERO_H
#pragma once
#include "stdlib.h"
#include <string>
#include "Creature.h"

//TODO LIST : ATTAQUE ULTIME, CLASSES, FINDRELIC

class Hero {
private:
    std::string name;
    int pv;
    int atk;
    int pvmax;
    int mana;
    int manamax;
    int potions;
    int coins;
    int lvl;
public:
    //constructeur
    Hero();
    Hero(std::string name, int pv, int atk, int pvmax, int mana, int manamax, int potions, int coins, int lvl);
    //methodes
    std::string getStats();
    void attackCreature(Creature &c);
    void takeDamage(int dmg);
    int getAtk();
    void usePotionHeal();
    void usePotionMana();
    //void fight(Creature &c);
    void castSpell(Creature &c);
    int flee();
    int getrandom(int min, int max);
    //void explore(Creature &c);
    void loot(Creature &c);
    //void shop(Creature &c);
    void buyPotion();
    void refineSword();
    void upgradeArmor();
    //void rest(Creature &c);
    void levelUp(int level);
    //void saveGame();
    //void loadGame(std::string filename);
    std::string getName();
    int getpv();
    int getmana();
    int getpvmax();
    int getmanamax();
    int getPotions();
    int getCoins();
    int getLvl();
    void setPv(int pv);
    void setMana(int mana);
    void setCoins(int coins);
    int steal(Creature &c);
    void drink();
    int listen();
    void findRelic();
};

#endif //CPPDND_HERO_H

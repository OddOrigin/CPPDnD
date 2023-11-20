#include <iostream>
#include "Hero.h"
#include "Creature.h"
#include "stdlib.h"
#include <random>
#include <fstream>

Hero::Hero(){

}

Hero::Hero(std::string name, int pv, int atk, int pvmax, int lvl, int mana, int manamax, int potions, int coins) : Entity(pv, atk, pvmax, name, lvl) {
    Entity(pv, atk, pvmax, name, lvl);
    this->mana = mana;
    this->potions = potions;
    this->manamax = manamax;
    this->coins = coins;

}

std::string Hero::getStats() {
    return "Nom: " + name + + " Niveau: " + std::to_string(lvl) + "  PV: " + std::to_string(pv) + "/" + std::to_string(pvmax) + " Atk: " + std::to_string(atk) + " Mana: " + std::to_string(mana) + "/" + std::to_string(manamax) + " Potions: " + std::to_string(potions) + " Coins: " + std::to_string(coins) + "\n";
}

std::string Hero::getName(){
    return this->name;
}



int Hero::getmana(){
    return this->mana;
}



int Hero::getmanamax(){
    return this->manamax;
}

int Hero::getPotions(){
    return this->potions;
}

int Hero::getCoins(){
    return this->coins;
}



void Hero::attackCreature(Creature &c) {
    printf("Un Hero attaque une Creature !\n");
    int atk1 = getrandom(0,this->atk) + 2;
    int atk2 = getrandom(0, c.getAtk());
    printf("attaque du Hero : %d\n", atk1);
    printf("attaque de la Creature : %d\n", atk2);
    if (atk1 > atk2) {
        if (getrandom(1,15)>14){
            int dmg = atk1;
            printf("Vous infligez un coup critique et infligez %d de dommages !\n", dmg);
            c.takeDamage(dmg);
        }
        else{
            int dmg =atk1-atk2;
            printf("Vous infligez %d de dommages !\n", dmg);
            c.takeDamage(dmg);
        }
    }
    else {
        if (getrandom(1,15)>14){
            int dmg = atk1;
            printf("La creature inflige un coup critique et vous inflige %d de dommages !\n", dmg);
            takeDamage(dmg);
        }
        else{
            int dmg = atk2-atk1;
            printf("La Creature vous inflige %d de dommages !\n", dmg);
            takeDamage(dmg);
        }


    }
}

void Hero::takeDamage(int dmg) {
    pv -= dmg;
    if (pv<=0){
        printf("Le Hero est mort !\n");
        exit(0);

    }
}

void Hero::usePotionHeal() {
    if (this->potions > 0) {
        int heal = getrandom(2,6) + getrandom(0,pvmax - 25);
        if (pv + heal > pvmax) {
            printf("Vous utilisez une potion et restaurez %d pv !\n", pvmax - pv);
            pv = pvmax;
        }
        else {
            printf("Vous utilisez une potion et restaurez %d pv !\n", heal);
            pv += heal;
        }
        this->potions--;
        printf("Vous avez maintenant %d potion(s) !\n", this->potions);
        printf("Vous avez maintenant %d pv !\n", this->pv);
    }
    else {
        printf("Vous n'avez plus de potion !\n");
    }
}

void Hero::usePotionMana(){
    if (this->potions > 0){
        int heal = 4 + getrandom(0,2);
        if (mana + heal > manamax) {
            printf("Vous utilisez une potion et restaurez %d mana !\n", pvmax - mana);
            mana = manamax;
        }
        else {
            printf("Vous utilisez une potion et restaurez %d mana !\n", heal);
            mana += heal;
        }
        this->potions--;
        printf("Vous avez maintenant %d potion(s) !\n", this->potions);
        printf("Vous avez maintenant %d mana !\n", this->mana);
    }
    else {
        printf("Vous n'avez plus de potion !\n");
    }
}

void Hero::castSpell(Creature &c) {
    if (mana < 4){
        printf("Vous n'avez pas assez de mana !\n");
    }
    else {
        int maxdmg = this->atk - 6;
        int dmg = 1 + getrandom(0,maxdmg);
        printf("Un Hero utilise un sort !\n");
        c.takeDamage(dmg);
        printf("Vous infligez %d de dommages !\n", dmg);
        mana -= 4;
        printf("Vous avez maintenant %d mana !\n", mana);
    }
}

int Hero::flee(){
    printf("Un Hero fuit !\n");
    int chance = getrandom(1, 10);
    if (chance > 5) {
        printf("Vous avez reussi !\n");
        return 1;
    } else {
        takeDamage(3);
        printf("Vous avez rate !\n");
        return 0;
    }
}

/*
void Hero::fight(Creature &c) {

    c.createCreature(this->lvl);
    std::cout << c.getName() << " : " << c.getStats();
    std::cout << "Hero : " << getStats();
    int i = 0;

    while (this->pv > 0 && c.getPv() > 0) {
        i++;
        printf("Tour %d\n", i);
        int turnDone = 0;
        while (turnDone != 1) {
            printf("Attaquer : 1 ; Potion de soin: 2 ; Sort : 3 ; Potion de mana : 4 ; Fuir : 5\n");
            int choix = 0;
            scanf("%d", &choix);
            fseek(stdin,0,SEEK_END);
            switch (choix) {
                case 0:
                    printf("Choix invalide !\n");
                    turnDone = 0;
                    break;
                case 1:
                    attackCreature(c);
                    turnDone = 1;
                    break;
                case 2:
                    usePotionHeal();
                    turnDone = 1;
                    break;
                case 3:
                    castSpell(c);
                    turnDone = 1;
                    break;
                case 4:
                    usePotionMana();
                    turnDone = 1;
                    break;
                case 5:
                    if (flee() == 0) {
                        turnDone = 1;
                        break;
                    } else {
                        explore(c);
                    }
                default:
                    printf("Choix invalide !\n");
                    turnDone = 0;
                    break;
            }
        }
        if (c.getPv() > 0) {
            printf("\n");
            c.attackHero(*this);
        }

        printf("\n");
        std::cout << c.getName() << " : " << c.getStats();
        std::cout << "Hero : " << getStats();
        printf("\n");
        printf("\n");
    };
    if (this->pv > 0){
        printf("Vous fouillez la depouille de la creature et ");
        loot(c);
        levelUp(c.getLevel());
        explore(c);
    }
}
*/

int Hero::getrandom(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

/*
void Hero::explore(Creature &c) {
    printf("Vous vous dirigez maintenant vers une autre direction !\n");
    int leftCrossroad = 0;
    while (leftCrossroad != 1) {
        printf("Explorer le reste de la foret : 1; chercher une boutique : 2 ; aller se reposer a une taverne (4 pieces) : 3 \n");
        int choix = 0;
        scanf("%d", &choix);
        fseek(stdin, 0, SEEK_END);
        switch (choix) {
            case 1:
                printf("La creature vous attaque !\n");
                fight(c);
                leftCrossroad = 1;
                break;
            case 2:
                printf("Vous arrivez a une boutique !\n");
                shop(c);
                leftCrossroad = 1;
                break;
            case 3:
                printf("Vous arrivez a une taverne !\n");
                rest(c);
                leftCrossroad = 1;
                break;
            default:
                printf("Choix invalide !\n");
                leftCrossroad = 0;
                break;
        }
    }
}
*/

void Hero::loot(Creature &c){
    if (getrandom(0, 10) > 5 ){
        printf("vous trouvez 1 potion et %d pieces d'or !\n",  c.getlvl() + 5);
        this->potions += 1;
        this->coins +=  c.getlvl() + 5;

    } else{
        if (getrandom(0, 10) > 7){
        printf("vous trouvez %d pieces d'or !\n", c.getlvl());
        this->coins += c.getlvl() ;
        }
        else{
            printf("vous ne trouvez rien !\n");
        }
    }
}

/*
void Hero::rest(Creature &c){
    if(this->coins < 4){
        printf("Vous n'avez pas assez d'or !\n");
        return;
    }
    else {
        if (getrandom(1, 10) > 5) {
            int foundcoins = getrandom(1, 6);
            printf("Par chance, vous trouvez %d pieces d'or !\n", foundcoins);
            this->coins += foundcoins;
        }
        printf("Vous vous reposez et payez 4 pieces d'or!\n");
        this->pv = this->pvmax;
        this->mana = this->manamax;
        this->coins -= 4;
        printf("Vous quittez la taverne \n");
        explore(c);
    }
}
*/

/*
void Hero::shop(Creature &c) {
    printf("Vous entrez dans la taverne !\n");
    int inshop = 1;
    while (inshop == 1) {
        printf("\n");
        printf("Vous avez %d pieces d'or !\n", this->coins);
        printf("Que voulez vous acheter?\n");
        printf("Une potion (4 pieces) : 1 ; Reforger votre lame (8 pieces) : 2 ; Ameliorer votre armure (6 pieces) : 3 ; S'en aller : 4 ");
        int choix = 0;
        scanf("%d", &choix);
        fseek(stdin,0,SEEK_END);
        switch (choix) {
            case 1:
                buyPotion();
                break;
            case 2:
                refineSword();
                break;
            case 3:
                upgradeArmor();
                break;
            case 4:
                printf("Vous repartez de la boutique \n");
                inshop = 0;
                break;
        }

    }
    explore(c);
}*/

void Hero::buyPotion() {
    if (this->coins >= 4) {
        this->coins -= 4;
        this->potions += 1;
        printf("Vous achetez une potion !\n");
    }
    else
        printf("Vous n'avez pas assez d'or !\n");

}

void Hero::refineSword() {
    if (this->coins >= 8) {
        this->coins -= 8;
        this->atk += 2;
        printf("Vous reforgez votre lame et votre attaque passe a %d !\n", this->atk);
    }
    else
        printf("Vous n'avez pas assez d'or !\n");
}

void Hero::upgradeArmor() {
    if (this->coins >= 6) {
        this->coins -= 6;
        this->pvmax += 5;
        this->pv += 5;
        printf("Vous ameliorez votre armure et vos pv max passent a %d !\n", this->pvmax);
    }
    else
        printf("Vous n'avez pas assez d'or !\n");
}

void Hero::levelUp(int level) {
    int lvlup = 0;
    if (level > this->lvl) {
        lvlup = level - this->lvl;
        this->lvl += lvlup;
    }
    else{
        if (level == this->lvl){
            lvlup = 1;
            this->lvl += lvlup;
        }
        lvlup = this->lvl - level;
        this->lvl += lvlup;
    }
    int i;
    printf("Vous montez de %d niveaux ! \n", lvlup);
    for (i = 0; i < lvlup; i++) {
        this->pvmax += 1;
        if (getrandom(1,10)>8){
            this->atk += 1;
        }
        if (getrandom(1,10)>9){
            this->manamax += 1;
        }

    }
    printf("\n");
}
/*
void Hero::saveGame() {
    std::ofstream myfile;
    std::string savename = "save" + getName() + ".csv";
    myfile.open(savename);
    myfile << "name,pv,atk,pvmax,mana,manamax,potions,coins,lvl\n";
    myfile << getName() << "," << getpv() << "," << getAtk() << "," << getpvmax() << "," << getmana() << "," << getmanamax() << "," << getPotions() << "," << getCoins() << "," << getLvl() << "\n";
    myfile.close();
    printf("Sauvegarde effectuee \n");
}

void Hero::loadGame(std::string filename) {
    std::ifstream myfile;
    myfile.open(filename);
    std::string line;
    getline(myfile, line);
    std::string name;
    int pv;
    int atk;
    int pvmax;
    int mana;
    int manamax;
    int potions;
    int coins;
    int lvl;
    std::stringstream lineStream(line);
    std::string cell;
    getline(lineStream, cell, ',');
    name = cell;
    getline(lineStream, cell, ',');
    pv = stoi(cell);
    getline(lineStream, cell, ',');
    atk = stoi(cell);
    getline(lineStream, cell, ',');
    pvmax = stoi(cell);
    getline(lineStream, cell, ',');
    mana = stoi(cell);
    printf("Donnees recuperees, application de la sauvegarde en cours \n");
}*/

void Hero::setPv(int pv) {
    this->pv = pv;
}

void Hero::setMana(int mana) {
    this->mana = mana;
}

void Hero::setCoins(int coins) {
    this->coins = coins;
}

int Hero::steal(Creature &c) {
    int roll = getrandom(1,10);
    if (roll < 3){
        printf("Vous n'avez pas reussi a voler !\n");
        return 0;
    }
    else{
        if (roll<8){
            int coinsfound = getrandom(1,7);
            this->coins += coinsfound;
            printf("Vous avez gagne %d or !\n", coinsfound);
            return 0;
        }
        else{
            printf("Alors que vous essayez de le voler, l'ivrogne se retourne et s'apprete a vous combattre !\n");
            int level = getrandom(this->lvl-1, this->lvl+2);
            c.createCustom(level, level + 5, level, "Ivrogne");
            return 1;
        }
    }

}

void Hero::drink() {
    printf("Vous saisissez alors le verre sur le comptoir, avant d'en boire le contenu d'une traite !\n");
    int roll = getrandom(1,4);
    switch(roll){
        case 1:
            printf("Malheur ! Le verre semblait empoisonne, vous perdez 3 pvmax !\n");
            this->pvmax -= 3;
            this->pv = this->pvmax;
            break;
        case 2:
            printf("Le contenu semble tres bon, mais sa forte contenance en alcool vous rend plus inapte a utiliser la magie, vous perdez 1 manamax \n");
            this->manamax -= 1;
            this->mana = this->manamax;
            break;
        case 3:
            printf("La boisson est plutot bonne, vous vous sentez revigore et gagnez 2 pvmax !\n");
            this->pvmax += 2;
            this->pv = this->pvmax;
            break;
        case 4:
            printf("La boisson est delicieuse ! Vous sentez vos courbatures disparaitre et gagnez 1 atk : \n");
            this->atk += 1;
            break;
    }
}

int Hero::listen() {
    int hasAnswered = 0;
    int answer;
    int roll = getrandom(1,4);
    std::string sentences[4] = {"En lisant un livre dans la bibliotheque, vous apprenez l'existence d'un tresor caché à l'exterieur de la ville","En ecoutant les conversations, vous entendez parler d'un ancien tresor perdu dans les egouts","Un homme vous approche, et vous dit : Dit gamin, tu savais qu'il y avait plein d'or cache a l'arriere de la taverne?","Un vieil homme vous approche et vous raconte l'histoire d'un tresor enterre dans la foret"};
    std::cout << sentences[roll] << std::endl;
    while (hasAnswered != 1){
        printf("Acceptez vous de vous y rendre ? \n");
        printf("1. Oui, 2. Non \n");
        scanf("%d", &answer);
        switch(answer){
            case 1:
                hasAnswered = 1;
                break;
            case 2:
                hasAnswered = 1;
                break;
            default:
                printf("Choix invalide \n");
                break;
        }
    }
    return answer;
}

void Hero::findRelic(){
    int roll = getrandom(1,4);
    switch(roll){
        case 1://epee, +1 ou 2 d'attaque
            this->atk += getrandom(1,2);
            printf("Vous trouvez une epee et votre attaque augmente \n");
            break;
        case 2://armure, +3/+5 pvmax
            this->pvmax += getrandom(3,5);
            printf("Vous trouvez une armure et vos pvmax augmente \n");
            break;
        case 3://artefact magique, +1 manamax
            this->manamax += 1;
            printf("Vous trouvez un artefact magique et votre manamax augmente \n");
            break;
        case 4://bouclier, +2pvmax, +1 atk
            this->pvmax += 2;
            this->atk += 1;
            printf("Vous trouvez un bouclier, vos pvmax et atk augmente \n");
            break;
    }
}



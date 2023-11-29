//
// Created by julie on 17/11/2023.
//

#include "Jeu.h"
#include "stdlib.h"
#include <iostream>

void Jeu::startGame() {
    printf("Bienvenue dans le jeu DnD !\n");
    printf("Creation du personnage\n");
    std::cout << this->hero.getStats();
    while(true){
        explore();
    }

}

Jeu::Jeu(Hero& h, Creature& c){
    this->hero = h;
    this->creature = c;
}

Hero Jeu::getHero(){
    return this->hero;
}

Creature Jeu::getCreature() {
    return this->creature;
}

void Jeu::explore() {
    printf("\n");
    printf("Vous vous dirigez maintenant vers une autre direction !\n");
    int leftCrossroad = 0;
    while (leftCrossroad != 1) {
        printf("Explorer le reste de la foret : 1; chercher une boutique : 2 ; aller se reposer a une taverne (4 pieces) : 3 \n");
        int choix = 0;
        scanf("%d", &choix);
        fseek(stdin, 0, SEEK_END);
        switch (choix) {
            case 1:
                if (this->hero.getrandom(1,10) > 7) {
                    printf("La creature vous attaque !\n");
                    this->creature.createCreature(this->hero.getlvl());
                    fight();
                }
                else{
                    rareEncounter();
                }
                leftCrossroad = 1;
                break;
            case 2:
                printf("Vous arrivez a une boutique !\n");
                shop();
                leftCrossroad = 1;
                break;
            case 3:
                printf("Vous arrivez a une taverne !\n");
                rest();
                leftCrossroad = 1;
                break;
            default:
                printf("Choix invalide !\n");
                leftCrossroad = 0;
                break;
        }
    }
}

void Jeu::rest(){
    if(this->hero.getCoins() < 4){
        printf("Vous n'avez pas assez d'or !\n");
        return;
    }
    else {
        printf("Vous vous reposez et payez 4 pieces d'or!\n");
        this->hero.setPv(this->hero.getpvmax()) ;
        this->hero.setMana(this->hero.getmanamax());
        this->hero.setCoins(this->hero.getCoins() - 4);
        int leftTaverne = 0;
        while (leftTaverne != 1) {
            printf("Apres vous etre repose, souhaitez-vous? \n");
            printf("Ecumer la taverne a la recherche de pieces : 1; Vous revigorer avec une boisson etrange : 2 ; Chercher des informations dans la taverne : 3 ; S'en aller : 4 \n");
            int choix = 0;
            scanf("%d", &choix);
            fseek(stdin, 0, SEEK_END);
            switch (choix) {
                case 1:
                    if(this->hero.steal(this->creature)==1){
                        fight();
                    }
                    leftTaverne = 1;
                    break;
                case 2:
                    this->hero.drink();
                    leftTaverne = 1;
                    break;
                case 3:
                    if(this->hero.listen()==1){
                        rollQuest();
                    };
                    leftTaverne = 1;
                    break;
                case 4:
                    printf("Vous quittez la taverne \n");;
                    leftTaverne = 1;
                    break;
                default:
                    printf("Choix invalide !\n");
                    break;
            }

        }
    }
}

void Jeu::fight() {
    std::cout << this->creature.getname() << " : " << this->creature.getStats();
    std::cout << "Hero : " << this->hero.getStats();
    int i = 0;

    while (this->hero.getpv() > 0 && this->creature.getpv() > 0) {
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
                    this->hero.attackCreature(this->creature);
                    turnDone = 1;
                    break;
                case 2:
                    this->hero.usePotionHeal();
                    turnDone = 1;
                    break;
                case 3:
                    this->hero.castSpell(this->creature);
                    turnDone = 1;
                    break;
                case 4:
                    this->hero.usePotionMana();
                    turnDone = 1;
                    break;
                case 5:
                    if (this->hero.flee() == 0) {
                        turnDone = 1;
                        break;
                    } else {
                        return;
                    }
                default:
                    printf("Choix invalide !\n");
                    turnDone = 0;
                    break;
            }
        }
        if (this->creature.getpv() > 0) {
            printf("\n");
            this->creature.attackHero(this->hero);
        }

        printf("\n");
        std::cout << this->creature.getname() << " : " << this->creature.getStats();
        std::cout << "Hero : " << this->hero.getStats();
        printf("\n");
        printf("\n");
    };
    if (this->hero.getpv() > 0){
        printf("Vous fouillez la depouille de la creature et ");
        this->hero.loot(this->creature);
        this->hero.levelUp(this->creature.getlvl());
    }
}


void Jeu::shop() {
    printf("Vous entrez dans la boutique !\n");
    int inshop = 1;
    while (inshop == 1) {
        printf("\n");
        printf("Vous avez %d pieces d'or !\n", this->hero.getCoins());
        printf("Que voulez vous acheter?\n");
        printf("Une potion (4 pieces) : 1 ; Reforger votre lame (8 pieces) : 2 ; Ameliorer votre armure (6 pieces) : 3 ; S'en aller : 4 ");
        int choix = 0;
        scanf("%d", &choix);
        fseek(stdin,0,SEEK_END);
        switch (choix) {
            case 1:
                this->hero.buyPotion();
                break;
            case 2:
                this->hero.refineSword();
                break;
            case 3:
                this->hero.upgradeArmor();
                break;
            case 4:
                printf("Vous repartez de la boutique \n");
                inshop = 0;
                break;
        }

    }
}

void Jeu::rollQuest() {
    printf("\n");
    printf("Vous arrivez a l'endroit decrit, et vous finissez par remarquer ce qui ressemble a un vieux coffre !\n");
    int roll = this->hero.getrandom(1, 7);
    int coins;
    switch (roll) {
        case 1:
            printf("Alors que vous vous approchez du coffre, vous sentez une presence, juste avant de vous faire envoyer au mur ! \n");
            this->creature.createCreature(this->hero.getlvl());
            fight();
            printf("Apres avoir triomphe, vous ouvrez le coffre, mais... il est vide !\n");
            break;
        case 2:
            printf("Alors que vous vous approchez du coffre, une silhouette s'impose devant vous ! \n");
            this->creature.createCreature(this->hero.getlvl());
            fight();
            printf("Apres avoir triomphe, vous ouvrez le coffre et ");
            this->hero.findRelic();
            break;
        case 3:
            printf("Vous vous approchez lentement du coffre, avant de l'ouvrir, mais... il est vide ! \n");
            break;
        case 4:
            printf("Vous vous approchez du coffre, l'ouvrant sans hésiter, et ");
            this->hero.findRelic();
            break;
        case 5:
            coins = this->hero.getrandom(8, 12);
            printf("Vous approchez le coffre, l'ouvrant avec precaution, et trouvez %d pieces d'or ! \n", coins);
            this->hero.setCoins(this->hero.getCoins() + coins);
            break;
        case 6:
            printf("Vous vous approchez du coffre, et alors que vous l'ouvrez, il se referme sur votre main que vous avez a peine le temps d'enlever ! \n");
            printf("Le coffre etait une mimique ! \n");
            this->creature.createCustom(this->hero.getlvl()*2+3, this->hero.getlvl()+3, this->hero.getlvl(), "Mimique");
            fight();
            break;
        case 7:
            printf("En approchant le coffre, une presence s'impose devant vous ! \n");
            this->creature.createCreature(this->hero.getlvl());
            fight();
            coins = this->hero.getrandom(8, 12);
            printf("Apres avoir triomphe, vous ouvrez le coffre et trouvez %d pieces d'or ! \n", coins);
            this->hero.setCoins(this->hero.getCoins() + coins);
            break;
    }
};

void Jeu::rareEncounter() {
    int roll = this->hero.getrandom(1, 10);
    switch (roll) {
        case 1: // fouille un cadavre, haute chance de trouver or/relique
            printf("Vous trouvez le cadavre d'un hero et decidez de le fouiller \n");
            roll = this->hero.getrandom(1, 10);
            if (roll < 3) {
                printf("Vous ne trouvez rien !\n");
            }
            else if (roll < 6) {
                int coins = this->hero.getrandom(3, 7);
                printf("Vous trouvez %d pieces d'or !\n", coins);
            }
            else {
                this->hero.findRelic();
            }
            break;
        case 2: //pnj quete

            break;
        case 3:
            printf("Vous voyez un batiment qui semble abandonné, et decidez d'y aller a la recherche de richesses \n");
            rollQuest();
            break;
        case 4: //rare shop
            printf("Alors que vous explorez la foret, un marchant itinerant vous approche \n");


            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9: //dungeon
            break;
        case 10: //chateau boss fight
            break;
    }
}

void Jeu::rareShop() {
    int roll = this->hero.getrandom(1, 5);
    switch (roll) {
        case 1:
            printf("Ce marchand vous propose des potions a un bas prix, 4 potions pour 8 pieces d'or \n");
            break;
        case 2:
            printf("Ce marchand vous propose une epee rarissime pour 15 pieces d'or \n");
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }

}

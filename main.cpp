#include <iostream>
#include "Creature.h"
#include "Hero.h"
#include "Jeu.h"

int main() {
    Hero h = Hero("Julien", 30, 10, 30, 10, 10, 3, 12,5);
    Creature c = Creature(13, 8, 3,13, "Loup");
    Jeu monJeu = Jeu(h, c);
    monJeu.startGame();
    return 0;
}



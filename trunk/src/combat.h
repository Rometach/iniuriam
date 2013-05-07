#ifndef __combat_h__
#define __combat_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso;
    char camp;
    int ordre;
    int posX;
    int posY;
    char orientation; /*Correspond à l'orientation du regard du combattant sur le terrain :
                        1 vers la gauche
                        2 vers le haut
                        3 vers la droite
                        4 vers le bas*/
} Combattant;

int mainCombat();

#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "parole.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2)
{
    dialogue->perso1=perso1;
    dialogue->perso2=perso2;
    if (getPersoFaction(perso1)==getPersoFaction(perso2)) /*Les personnages sont alliés*/
    {
        dialogue->humeur=50;
    }
    else if ((getPersoFaction(perso1)==0)&&(getPersoFaction(perso2)==1))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else if ((getPersoFaction(perso1)==1)&&(getPersoFaction(perso2)==0))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else    /*L'un des personnages est marchand...*/
    {
        dialogue->humeur=25;
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "case.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void initCase(char typeCase , Case* C)
{
	switch (typeCase) {
case 0 : /** sol */
	C->type = 0;
	C->praticable = 1;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;

case 1 :	/** chemin */
	C->type = 1;
	C->praticable = 1;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;

case 2 :	/** marais */
	C->type = 2;
	C->praticable = 1;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;

case 3 :	/** mur */
	C->type = 3;
	C->praticable = 0;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;
	
case 4 :	/** arbre */
	C->type = 4;
	C->praticable = 0;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;
	
case 5 :	/** eau */
	C->type = 5;
	C->praticable = 0;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;

case 6 :	/** montagne */
	C->type = 6;
	C->praticable = 0;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;
	
case 7 :	/** gouffre */
	C->type = 7;
	C->praticable = 0;
	C->personnage = 0;
	C->piege = 0;
	C->objet = 0;
	break;
	
default: 
	printf("Erreur\n");
	}
}

char assetPraticable(Case* C){
	return C->praticable;
}

char assetPersonnage(Case* C){
	return C->personnage;
}

char assetPiege(Case* C){
	return C->piege;
}

Objet* assetObjet(Case* C){
	return C->objet;
}

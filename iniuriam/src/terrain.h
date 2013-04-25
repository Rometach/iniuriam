#ifndef __terrain_h__
#define __terrain_h__

#include <stdio.h>
#include <stdlib.h>
#include "case.h"
#include "personnage.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/


typedef struct
{
	char id;
	Case* terrain;
	Personnage * liste;

} Terrain;

/**
* \brief Preconditions : terr n'a pas déjà été initialisé
* <br /> Postconditions : terr est initialisé
*/
void initTerrain(Terrain* terr, char id);

/**
* \brief Preconditions : terr est initialisé
* <br /> Postconditions : terr est remplis
*/
void remplirTerrain(Terrain* terr);

/**
* \brief Preconditions : terr est initialisé et remplis
* <br /> Postconditions : affiche terr
*/
void afficheTerrain(Terrain* terr);

void libereTerrain( Terrain* T);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "objet.h"
#include "personnage.h"
#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int main (int argc, char *argv[])
{
	Terrain* terrain;
	
	initTerrain(terrain);
	
	afficheTerrain(terrain);
	
	libereTerrain(terrain);
	
    return 0;
}

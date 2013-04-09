#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stock.h"
#include "personnage.h"
#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int mainTerrain2 (int argc, char *argv[])
{
	Terrain* terrain;

	initTerrain(terrain);

	afficheTerrain(terrain);

	libereTerrain(terrain);

    return 0;
}

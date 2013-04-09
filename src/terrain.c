#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ncurses.h"
#include "affichageNcurses.h"
#include "case.h"
#include "terrain.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 22

void initTerrain(Terrain* T){
	int i,j;
	T->terrain = (Case*)malloc(TAILLE_MAX*TAILLE_MAX*sizeof(Case));
	FILE* fTerr= fopen("data/Terrains.txt", "r");
	char ligne[TAILLE_MAX];
	if (fTerr!=NULL){
		for (i=0; i<T->id*4; i++){
			fgets(ligne, TAILLE_MAX+2, fTerr);
		}
		for (i=0; i<TAILLE_MAX; i++){
			fgets(ligne,TAILLE_MAX+2,fTerr);		
			for(j=0; j<TAILLE_MAX; j++){
				initCase(ligne[j]-'0', &(T->terrain[(i*21)+j]));
			}
		}
        fclose(fTerr);
        printf("Le terrain a bien ete initialise\n");
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Terrains.txt\n");
    }
}

void afficheTerrain(Terrain* T)
{	int i, j;
	for(i = 0; i<TAILLE_MAX; i++){
		for(j = 0; j<TAILLE_MAX; j++){
			printf("%d", T->terrain[(i*21)+j].type);
		}
		printf("\n");
	}
}

void libereTerrain( Terrain* T){
	free(T->terrain);
}

int main (int argc, char *argv[])
{
	Terrain terrain;
	WINDOW win;
	
	initTerrain(&terrain);
	
	initFenetre(&win);
	
	afficheTerrainN(&terrain, &win );
	
	libereTerrain(&terrain);
	
    return 0;
}

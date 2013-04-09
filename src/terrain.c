#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "case.h"
#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 23

void initTerrain( Terrain* T){
	int i,j;
	T = (Case*)malloc(TAILLE_MAX*TAILLE_MAX*sizeof(Case));
	FILE* fTerr= fopen("data/Terrains.txt", "r");
	char ligne[TAILLE_MAX];
	printf("OOOOOOO\n");
	if (fTerr!=NULL){
		for (i=4; i<TAILLE_MAX; i++){
			printf("11111111\n");
			for(j=0; j<TAILLE_MAX; j++){
				printf("2222222222\n");
				fgets(ligne,TAILLE_MAX,fTerr);
				initCase(ligne[j]-'0', &(T->terrain[(i*23)+j]));
				printf("%d %d", ligne[j], ligne[j]-'0');
			}
		}
        fclose(fTerr);
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Terrains.txt\n");
    }
}

void afficheTerrain(Terrain* terr)
{	int i, j;
	
	for(i = 0; i<TAILLE_MAX; i++){
		for(j = 0; j<TAILLE_MAX; j++){
			printf("%d", terr->terrain[i+j].type);
		}
	}
}

void libereTerrain( Terrain* T){
	free(T);
}

int main (int argc, char *argv[])
{
	Terrain* terrain=NULL;
	
	initTerrain(terrain);
	
	afficheTerrain(terrain);
	
	libereTerrain(terrain);
	
    return 0;
}

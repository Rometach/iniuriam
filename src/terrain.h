
#ifndef TERRAIN_H
# define TERRAIN_H

#include "SDL/SDL.h"
#include "tile.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct
{
    int nbrTile;
    int decalageX;
    int defilY;
    int tileSel;

    unsigned int hauteur;
    unsigned int largeur;

    Tile* tabChipset;
    SDL_Surface* chipset;

    unsigned int *carte;        /* pointeur vers la carte (allocation dynamique) */

} Terrain;

void initTerrain(Terrain* ter);

void remplirStructTerrain(Terrain* ter);

void setNbrTile(Terrain* ter, int nbrTile);

void setDecalageX(Terrain* ter, int x);

void setDefilY(Terrain* ter, int y);

void setTileSel(Terrain* ter, int selec);

void setHauteur(Terrain* ter, unsigned int hauteur);

void setLargeur(Terrain* ter, unsigned int largeur);

void setTabChipset(Terrain* ter, int i, Tile* tile);

void setCarte(Terrain *ter, int i, int numTile);

int getNbrTile(Terrain* ter);

int getDecalageX(Terrain* ter);

int getDefilY(Terrain* ter);

int getTileSel(Terrain* ter);

unsigned int getHauteur(Terrain* ter);

unsigned int getLargeur(Terrain* ter);

Tile* getTabChipset(Terrain* ter, int i);

int getCarte(Terrain *ter, int i);

void sauvTerrain(Terrain* ter, char* nomFichier, char* nomChipset);

void chargeTerrain(Terrain* ter, char* nomFichier);

void detruitTerrain(Terrain* ter);

#endif


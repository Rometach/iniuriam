
#ifndef TERRAIN_H
# define TERRAIN_H

#include "SDL/SDL.h"
#include "tile.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct
{
    int nbrTile;
    int defilY;
    int decalageX;
    int tile_sel;
    unsigned int largeur;
    unsigned int hauteur;

    Tile* tabChipset;
    SDL_Surface* chipset;

    unsigned int *carte;        /* pointeur vers la carte (allocation dynamique) */


} Terrain;

void initTerrain(Terrain* ter);

void remplirTerrain(Terrain* ter);

int getNbrTile(Terrain* ter);

Tile* getTabChipset(Terrain* ter);

int getTileCarte(Terrain* ter, int i);

SDL_Surface* getChipset(Terrain* ter);

void setNbrTile(Terrain* ter, int nbrTile);

void setTabChipset(Terrain* ter);

void setChipset(Terrain* ter);

void setTileCarte(Terrain* ter, int i, int tile_sel);

void sauvegardeTerrain(Terrain* ter);

void chargeTerrain(Terrain* ter);

void affChipset(Terrain* ter, SDL_Surface* ecran);

void affCarte(Terrain* ter, SDL_Surface* ecran);

void event(Terrain* ter, SDL_Surface* ecran);

void detruitTerrain(Terrain* ter);

#endif



#ifndef AFFICHAGE_SDL_H
# define AFFICHAGE_SDL_H

#include "SDL/SDL.h"
#include "tile.h"
#include "stdlib.h"
#include "stdio.h"



void affChipset(Terrain* ter, SDL_Surface* ecran);

void affCarte(Terrain* ter, SDL_Surface* ecran);

void eventSDL(Terrain* ter, SDL_Surface* ecran);


#endif

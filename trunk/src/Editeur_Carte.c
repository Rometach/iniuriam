#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "terrain.h"
#include "affichage_sdl.h"
#include "Editeur_Carte.h"

#define TAILLE 700
#define TAILLE_CARTE 480

int mainEdit()
{
    Terrain terrain;
    SDL_Surface* ecran = NULL;
    initTerrain(&terrain);
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE, TAILLE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    remplirStructTerrain(&terrain);

    affChipset(&terrain, ecran);
    affCarte(&terrain, ecran);

    eventSDL(&terrain, ecran);

    detruitTerrain(&terrain);
    SDL_Quit();

    return 0;
}

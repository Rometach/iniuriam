#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SDL/SDL.h"
#include "parole.h"
#include "affichage_sdl.h"
#include "deplacement.h"
#include "combat.h"
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int main (int argc, char **argv)
{
    Terrain terrain;
    SDL_Surface* ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    initTerrain(&terrain);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    Personnage hero;

    initPerso(&hero);
    chargeTerrain(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");

    affCarte(&terrain, ecran);
    affPerso(&hero, ecran);
    eventJeuSDL(&hero, &terrain, ecran);

    detruitTerrain(&terrain);
    SDL_Quit();

    return 0;
}

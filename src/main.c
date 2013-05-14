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
    Personnage hero;
    Personnage pnj;
    SDL_Init(SDL_INIT_VIDEO);
    terInit(&terrain);
    initPerso(&hero);
    initPerso(&pnj);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terCharger(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");
    pnj.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
    setPersoPosX(&pnj, TILE_LARGEUR*5);
    setPersoPosY(&pnj, TILE_HAUTEUR*0);

    eventJeuSDL(&hero, &pnj, &terrain, ecran);

    terLibere(&terrain);
    SDL_Quit();


    return 0;
}

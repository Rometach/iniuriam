#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SDL/SDL.h"
#include "parole.h"
#include "affichage_sdl.h"
#include "deplacement.h"
#include "combat.h"
#include "constante.h"
#include "time.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int main (int argc, char **argv)
{
    Dialogue dialogue;

    /*Terrain terrain;
    SDL_Surface* ecran = NULL;
    Personnage hero;
    Personnage pnj;
    SDL_Init(SDL_INIT_VIDEO);
    terInit(&terrain);
    persoInit(&hero);
    persoInit(&pnj);
    dialogueInit(&dialogue, &hero, &pnj);

    Objet *tab;

    tab=(Objet*)malloc(40*sizeof(Objet));
    initialiserTousLesObjets(tab);

    srand(time(NULL));
    nouveauPerso (&hero, "Toromis", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&pnj, "Babar", 1, 1, 1, 1, 0, 100,tab);


    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terCharger(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");
    pnj.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
    setPersoPosX(&pnj, TILE_LARGEUR*5);
    setPersoPosY(&pnj, TILE_HAUTEUR*0);

    eventJeuSDL(&hero, &pnj, &terrain, &dialogue, ecran);

    persoLibere(&pnj);
    persoLibere (&hero);
    free(tab);
    terLibere(&terrain);
    SDL_Quit();*/

    return 0;
}

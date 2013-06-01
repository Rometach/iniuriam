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
#include "menu.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int main (int argc, char **argv)
{
    Dialogue dialogue;
    Terrain terrain;
    SDL_Surface* ecran = NULL;
    Personnage hero;
    Personnage pnj;
    Personnage ennemi;
    SDL_Init(SDL_INIT_VIDEO);
    terInit(&terrain);
    persoInit(&hero);
    persoInit(&pnj);
    persoInit(&ennemi);
    dialogueInit(&dialogue, &hero, &pnj);
    Objet *tabObjets=NULL;
    Mission tutoriel;
    missionInit(&tutoriel);
    missionDefinir(&tutoriel, 1, tabObjets);

    initialiserTousLesObjets(&tabObjets);

/*   mainMenu();*/
    srand(time(NULL));
    nouveauPerso (&hero, "Toromis", 1, 1, 2, 1, 0, 100, tabObjets);

    nouveauPerso (&ennemi, "Mechant", 1, 1, 1, 1, 0, 100, tabObjets);

    nouveauPerso (&pnj, "Babar", 1, 1, 1, 1, 0, 100, tabObjets);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terCharger(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
    pnj.avatar=SDL_LoadBMP("data/Media/cyborg.bmp");
    ennemi.avatar=SDL_LoadBMP("data/Media/humain.bmp");

    setPersoPosX(&ennemi, TILE_LARGEUR*5);
    setPersoPosY(&ennemi, TILE_HAUTEUR*1);

    eventJeuSDL(&hero, &pnj, &ennemi, &tutoriel, tabObjets, &terrain, &dialogue, ecran);

    persoLibere(&ennemi);
    persoLibere (&hero);
    persoLibere(&pnj);
    libererTousLesObjets(&tabObjets);
    terLibere(&terrain);
    SDL_Quit();

    return 0;
}

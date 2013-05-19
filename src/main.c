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
    dialogueInit(&dialogue, &hero, &ennemi);
    int i;
    Objet *tab=NULL;
    int max = getNbObjet();

    tab=(Objet*)malloc(max*sizeof(Objet));
    initialiserTousLesObjets(tab);

    srand(time(NULL));
    nouveauPerso (&hero, "Toromis", 1, 1, 1, 1, 0, 100, tab);
    nouveauPerso (&ennemi, "Babar", 1, 1, 1, 1, 0, 100, tab);
    nouveauPerso (&pnj, "Babar", 1, 1, 1, 1, 0, 100, tab);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terCharger(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/perso.bmp");
    pnj.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
    ennemi.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");

    for(i=0; i<hero.inventaire.nbObjet; i++)
    {
    pnj.inventaire.st[i].objet->icon=SDL_LoadBMP("data/Chipsets/perso.bmp");
    hero.inventaire.st[i].objet->icon=SDL_LoadBMP("data/Chipsets/perso.bmp");
//    ennemi.inventaire.st[i].objet->icon=SDL_LoadBMP("data/Chipsets/perso.bmp");
    }
    hero.inventaire.st[0].quantite=2;
    setPersoPosX(&ennemi, TILE_LARGEUR*5);
    setPersoPosY(&ennemi, TILE_HAUTEUR*0);

    eventJeuSDL(&hero, &pnj, &ennemi, &terrain, &dialogue, ecran);

    persoLibere(&ennemi);
    persoLibere (&hero);
    free(tab);
    terLibere(&terrain);
    SDL_Quit();

    return 0;
}

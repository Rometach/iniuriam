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
#include "liste_perso.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int main (int argc, char **argv)
{
    SDL_Surface* ecran = NULL;
    TTF_Font *police = NULL;

    Partie jeu;
    Objet *tabObjet=NULL;
    Mission missionActuelle;
    char chemin [30];
    char c,d;

    int nbPNJ;
    Liste_Perso *tabPnj=NULL;

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);
    TTF_Init();
    police = TTF_OpenFont("data/Jester.ttf", 30);

    partieVide(&jeu);
    initialiserTousLesObjets(&tabObjet);
    Terrain terrain;
    terInit(&terrain);

    c=afficherDebut(ecran,police);
    if (c)
    {
        d=afficherMenu (ecran, 0, police,  &jeu,tabObjet);

        if (d)
        {
            getPartieMissionActuelle(&jeu,&missionActuelle,tabObjet);
            sprintf(chemin,"data/Cartes/carte%d.map",getPartieNumCarte(&jeu));
            terCharger(&terrain, chemin);
            initialiserTousLesPNJ2(&tabPnj,tabObjet);
            nbPNJ=getPNJCarte(&tabPnj,getPartieNumCarte(&jeu));
            eventJeuSDL(getPartieJoueurs(&jeu), getPartieNbJoueur(&jeu), tabPnj, nbPNJ, &missionActuelle, tabObjet, &terrain, ecran);
            libererTousLesPNJ2(&tabPnj);
        }
    }
    libererTousLesObjets(&tabObjet);
    partieLibere(&jeu);
    terLibere(&terrain);

    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return 0;
}

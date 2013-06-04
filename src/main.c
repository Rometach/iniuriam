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


//    Objet *tabO;
//    Liste_Perso* tabPNJ;
//
//    initialiserTousLesObjets(&tabO);
//    initialiserTousLesPNJ2(&tabPNJ, tabO);
//
//    libererTousLesObjets(&tabO);
//    libererTousLesPNJ2(&tabPNJ);
//
//    return 0;


    Partie partieTest;
    int i, nbrHero = 3, nbrPnj = 4;
    Objet *tabObjets=NULL;
    SDL_Surface* ecran = NULL;
    TTF_Font *police = NULL;
    Terrain terrain;
    terInit(&terrain);
    terCharger(&terrain, "data/Cartes/carte.map");

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ecran = SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    police = TTF_OpenFont("data/Jester.ttf", 30);

   partieVide(&partieTest);

   afficherMenu (ecran, 0, police,  &partieTest, tabObjets);

    srand(time(NULL));


    Liste_Perso* pnj=NULL;
    /*Liste_Perso* liste=NULL;*/
    Personnage* heros;

    heros=(Personnage*)malloc(nbrHero*sizeof(Personnage));
    pnj=(Liste_Perso*)malloc(nbrPnj*sizeof(Liste_Perso));

    initialiserTousLesObjets(&tabObjets);

    for(i=0; i<nbrPnj; i++)
    {
        listePersoInit(&pnj[i], 1, terrain.numCarte);
    }

    Mission tutoriel;
    missionInit(&tutoriel);
    missionDefinir(&tutoriel, 1, tabObjets);

    nouveauPerso (&heros[0], "Toromis", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&heros[1], "Plop", 3, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&heros[2], "Oh!", 4, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (pnj[0].perso, "Babar", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&pnj[1].perso[0], "Mechant", 1, 1, 1, 1, 0, 100, tabObjets);
    nouveauPerso (pnj[2].perso, "Babar", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&pnj[3].perso[0], "VillainI", 2, 1, 1, 1, 0, 100, tabObjets);

    setPersoPosX(pnj[1].perso, TILE_LARGEUR*5);
    setPersoPosY(pnj[1].perso, TILE_HAUTEUR*1);

    setPersoPosX(pnj[2].perso, TILE_LARGEUR*1);
    setPersoPosY(pnj[2].perso, TILE_HAUTEUR*5);

    setPersoPosX(pnj[3].perso, TILE_LARGEUR*5);
    setPersoPosY(pnj[3].perso, TILE_HAUTEUR*5);

 //   eventJeuSDL(getPartieJoueurs(&partieTest), getPartieNbJoueur(&partieTest), pnj, nbrPnj, &tutoriel, tabObjets, &terrain, ecran);
    eventJeuSDL(heros, nbrHero, pnj, nbrPnj, &tutoriel, tabObjets, &terrain, ecran);
    for(i=0; i<nbrHero; i++)
    {
        persoLibere(&heros[i]);
    }

    for(i=0; i<getNbPNJ(); i++)
    {
        listePersoLibere(&pnj[i]);
    }
    TTF_CloseFont(police);
    TTF_Quit();
    listePersoLibere(pnj);
    tabListePersoLibere(pnj);
    libererTousLesObjets(&tabObjets);
    terLibere(&terrain);
    free(heros);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return 0;
}

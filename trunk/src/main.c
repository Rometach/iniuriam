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
    int i;
    Objet *tabObjets=NULL;

    initialiserTousLesObjets(&tabObjets);

    srand(time(NULL));
    nouveauPerso (&hero, "Toromis", 1, 1, 1, 1, 0, 100, tabObjets);
    nouveauPerso (&ennemi, "Mechant", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&pnj, "Babar", 1, 1, 1, 1, 0, 100, tabObjets);

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
    ennemi.inventaire.st[i].objet->icon=SDL_LoadBMP("data/Chipsets/perso.bmp");
    }
    hero.inventaire.st[0].quantite=2;
    setPersoPosX(&ennemi, TILE_LARGEUR*5);
    setPersoPosY(&ennemi, TILE_HAUTEUR*0);
    for (i=0;i<3;i++)
    {
        printf("%d\n", ennemi.inventaire.st[i].objet->valeur);
    }

    eventJeuSDL(&hero, &pnj, &ennemi, &terrain, &dialogue, ecran);

    persoLibere(&ennemi);
    persoLibere (&hero);
    libererTousLesObjets(&tabObjets);
    terLibere(&terrain);
    SDL_Quit();
//    mainMenu();
    return 0;
/*
    Personnage *liste;
    Objet *tab=NULL;
    int i,j,type=1;
    char arene [TAILLE_MAX][TAILLE_MAX],ligne [TAILLE_MAX+2];

    srand(time(NULL));

    liste=(Personnage*)malloc(4*sizeof(Personnage));

    initialiserTousLesObjets(tab);

    nouveauPerso (&liste[0], "Toromis", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[1], "Rometach", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[2], "Babar", 2, 1, 2, 1, 0, 100,tab);
    nouveauPerso (&liste[3], "BabarII", 2, 1, 2, 1, 0, 100,tab);

    FILE* fTerr=fopen("data/Terrains.txt", "r");

    if (fTerr!=NULL)
    {
        for (i=0; i<4;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<(TAILLE_MAX+2)*(type-1);i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<TAILLE_MAX;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
            for (j=0;j<TAILLE_MAX;j++)
            {
                arene[i][j]=ligne[j]-'0';
            }
        }
        fclose (fTerr);

        afficherTab2D (arene);
        combat (liste,4,arene);

    }
    persoLibere(&liste[0]);
    persoLibere(&liste[1]);
    persoLibere(&liste[2]);
    persoLibere(&liste[3]);
    free (liste);
    libererTousLesObjets(tab);
    return 0;*/
}

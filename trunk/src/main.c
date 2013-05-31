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
    mainMission();
    return 0;

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

    srand(time(NULL));
    nouveauPerso (&hero, "Toromis", 1, 1, 1, 1, 0, 100, tabObjets);
    nouveauPerso (&ennemi, "Mechant", 2, 1, 2, 1, 0, 100, tabObjets);
    nouveauPerso (&pnj, "Babar", 1, 1, 1, 1, 0, 100, tabObjets);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terCharger(&terrain, "data/Cartes/save.map");
    hero.avatar=SDL_LoadBMP("data/Chipsets/pnj.bmp");
    pnj.avatar=SDL_LoadBMP("data/Media/cyborg.bmp");
    ennemi.avatar=SDL_LoadBMP("data/Media/humain.bmp");

    setPersoPosX(&ennemi, TILE_LARGEUR*5);
    setPersoPosY(&ennemi, TILE_HAUTEUR*0);

    eventJeuSDL(&hero, &pnj, &ennemi, &tutoriel, tabObjets, &terrain, &dialogue, ecran);

    persoLibere(&ennemi);
    persoLibere (&hero);
    persoLibere(&pnj);
    libererTousLesObjets(&tabObjets);
    terLibere(&terrain);
    SDL_Quit();
    /*FMOD_SYSTEM *system;
    FMOD_SOUND *musique;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(system, "data/Media/GRAMATIK-Just Jammin'.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

    FMOD_Sound_SetLoopCount(musique, -1);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);*/

//    mainMenu();
    /*FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);*/
    return 0;

  /*  Personnage *liste;
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

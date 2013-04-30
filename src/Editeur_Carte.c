#include "stdlib.h"
#include "assert.h"
#include "terrain.h"
#include "affichage_sdl.h"

#define TAILLE 700
#define TAILLE_CARTE 480

int main( int argc, char** argv )
{
    int i;
    Terrain terrain;
    SDL_Surface* ecran = NULL;
    SDL_Event* event=NULL;
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

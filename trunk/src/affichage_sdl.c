#include "SDL/SDL.h"
#include "terrain.h"
#include "tile.h"
#include "affichage_sdl.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void affChipset(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    position.x = 0;
    position.y = 0;

    for(i=ter->defilY;i<getNbrTile(ter); i++)
       {
            tile.w=TILE_LARGEUR;
            tile.h=TILE_HAUTEUR;

            tile.x=getPosX(ter->tabChipset[i]);
            tile.y=getPosY(ter->tabChipset[i]);

            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.w=2;
            position.h=2;
            SDL_FillRect(SDL_GetVideoSurface(),&position,
                         ((getCollision(ter->tabChipset[i]))==0)?
                         SDL_MapRGB(SDL_GetVideoSurface()->format,255,0,0)
                         : SDL_MapRGB(SDL_GetVideoSurface()->format,0,255,0));

            position.x+= TILE_LARGEUR;

            if(position.x>=ter->decalageX*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
           }
        }
            SDL_Flip(ecran);
}

void affEditeur(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    affChipset(ter, ecran);
    position.x = (ter->decalageX+1)*TILE_LARGEUR;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i=0; i<TAILLE_CARTE; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=TAILLE_CARTE+(ter->decalageX+1)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=(ter->decalageX+1)*TILE_LARGEUR;
            }
    }
    SDL_Flip(ecran);
}

void affCarte(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i=0; i<TAILLE_CARTE; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=TAILLE_CARTE)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
            }
    }
    SDL_Flip(ecran);

}

void affPerso(Personnage* hero, SDL_Surface* surfPerso, SDL_Surface* ecran)
{
    SDL_Rect position;

    position.x = hero->posX;
    position.y = hero->posY;
    SDL_BlitSurface(surfPerso, NULL, ecran, &position);

    SDL_Flip(ecran);
}

void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran )
{
    int i;
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                 if(event.key.keysym.sym==SDLK_PAGEUP)
                    {
                       if(ter->defilY>0){ ter->defilY-=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_PAGEDOWN)
                    {
                        if(ter->defilY<ter->nbrTile-TAILLE_FENETRE/TILE_HAUTEUR){ter->defilY+=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_s) /* SAVE */
                    {
                        sauvTerrain(ter, "save.map", "HOTEL02.bmp");
                    }
                    else if(event.key.keysym.sym==SDLK_l) /* LOAD */
                    {   detruitTerrain(ter);
                        initTerrain(ter);
                        chargeTerrain(ter, "save.map");
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {   ter->tileSel=((event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTile;
                    if(ter->tileSel>=ter->nbrTile) ter->tileSel=ter->nbrTile-1;
                }
                else if(event.button.x>ter->decalageX*TILE_LARGEUR)
                {
                    i=((event.button.y/TILE_HAUTEUR)*(TAILLE_CARTE/TILE_LARGEUR)+event.button.x/TILE_LARGEUR-ter->decalageX-1);

                    if(i>=TAILLE_CARTE) i=TAILLE_CARTE-1;
                    setCarte(ter, i, ter->tileSel);
                }
            }

            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {
                    i=(event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY;
                   setCollision(&ter->tabChipset[i], (ter->tabChipset[i].collision+1)%2);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
        affEditeur(ter, ecran);
    }
}

void eventJeuSDL(Personnage* hero, Terrain* ter, SDL_Surface* surfPerso, SDL_Surface* ecran)
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                    if(event.key.keysym.sym==SDLK_RIGHT)
                    {   if(getCollision(ter->tabChipset[ter->carte[(hero->posX+TILE_LARGEUR)/TILE_LARGEUR+ter->largeur*(hero->posY/TILE_HAUTEUR)]])==1)
                        {hero->posX+=TILE_LARGEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_LEFT)
                    {   if(getCollision(ter->tabChipset[ter->carte[(hero->posX-TILE_LARGEUR)/TILE_LARGEUR+ter->largeur*(hero->posY/TILE_HAUTEUR)]])==1)
                        {hero->posX-=TILE_LARGEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_DOWN)
                    {   if(getCollision(ter->tabChipset[ter->carte[hero->posX/TILE_LARGEUR+ter->largeur*((hero->posY+TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {hero->posY+=TILE_HAUTEUR;}
                    }
                    else if(event.key.keysym.sym==SDLK_UP)
                    {   if(getCollision(ter->tabChipset[ter->carte[hero->posX/TILE_LARGEUR+ter->largeur*((hero->posY-TILE_HAUTEUR)/TILE_HAUTEUR)]])==1)
                        {hero->posY-=TILE_HAUTEUR;}
                    }
                    affCarte(ter, ecran);
                    affPerso(hero, surfPerso, ecran);
                }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
            }
        }
    }
}

#include "SDL/SDL.h"
#include "terrain.h"
#include "tile.h"
#include "affichage_sdl.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#define TILE_LARGEUR  16
#define TILE_HAUTEUR 16
#define TAILLE_CARTE 480
#define TAILLE_CHIPSET 96


void affChipset(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
//    unsigned int j;

    position.x = 0;
    position.y = 0;



    /* for(i=0; i<ter->hauteur; i++)
    {  for(j=0;j<ter->largeur; j++)

        {   tile.w=TILE_LARGEUR;
            tile.h=TILE_HAUTEUR;
            tile.x=getPosX(ter->tabChipset[(i*ter->largeur)+j]);
            tile.y=getPosY(ter->tabChipset[(i*ter->largeur)+j]);

            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=ter->decalageX)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
           }
        }
    }*/

    for(i=0;i<ter->nbrTile; i++)
        {
            tile.w=TILE_LARGEUR;
            tile.h=TILE_HAUTEUR;
            tile.x=getPosX(ter->tabChipset[(i+ter->defilY)%ter->nbrTile]);
            tile.y=getPosY(ter->tabChipset[(i+ter->defilY)%ter->nbrTile]);

            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.w=2;
            position.h=2;
            SDL_FillRect(SDL_GetVideoSurface(),&position,
                         ((getCollision(ter->tabChipset[(i+ter->defilY)%ter->nbrTile]))==0)?
                         SDL_MapRGB(SDL_GetVideoSurface()->format,255,0,0)
                         : SDL_MapRGB(SDL_GetVideoSurface()->format,0,255,0));


            position.x+= TILE_LARGEUR;

            if(position.x>=ter->decalageX)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
           }
        }
            SDL_Flip(ecran);
}

void affCarte(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    position.x = ter->decalageX+16;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i=0; i<TAILLE_CARTE; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>TAILLE_CARTE+ter->decalageX)
            {
                position.y+= TILE_HAUTEUR;
                position.x=ter->decalageX+16;
            }
    }
    SDL_Flip(ecran);
}

void eventSDL(Terrain* ter, SDL_Surface* ecran )
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
                    /*if(event->key.keysym.sym==SDLK_RIGHT)
                    {
                        if (map->offsetX<(map->width*TILE_WIDTH-800)) map->offsetX++;
                    }
                    else if(event->key.keysym.sym==SDLK_LEFT)
                    {
                        if (map->offsetX!=0) map->offsetX--;
                    }
                    else if(event->key.keysym.sym==SDLK_DOWN)
                    {
                        if (map->offsetY<(map->height*TILE_HEIGHT-600)) map->offsetY++;
                    }
                    else if(event->key.keysym.sym==SDLK_UP)
                    {
                        if (map->offsetY!=0) map->offsetY--;
                    }
            /* CHIPSET */
                  /*  else */if(event.key.keysym.sym==SDLK_PAGEUP)
                    {
                        ter->defilY-=ter->decalageX/TILE_LARGEUR;
                    }
                    else if(event.key.keysym.sym==SDLK_PAGEDOWN)
                    {
                        ter->defilY+=ter->decalageX/TILE_LARGEUR;
                    }
            /* FONCTION SPECIALES */
                    /*else if(event->key.keysym.sym==SDLK_f) /* FILL */
                /* {
                        for(i=0;i<map->width;i++)
                        for(j=0;j<map->height;j++)
                        GET_TILE(i,j,map)=map->tile_sel;
                    }*/
                    else if(event.key.keysym.sym==SDLK_s) /* SAVE */
                    {
                        sauvTerrain(ter, "../data/Cartes/save.map", "../data/Chipsets/HOTEL02.bmp");
                    }
                    else if(event.key.keysym.sym==SDLK_l) /* LOAD */
                    {
                            detruitTerrain(ter);
                            initTerrain(ter);
                            chargeTerrain(ter, "../data/Cartes/save.map");
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x<ter->decalageX)
                {   ter->tileSel=((event.button.y/TILE_HAUTEUR)*(ter->decalageX/TILE_LARGEUR)+event.button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTile;
                    if(ter->tileSel>=ter->nbrTile) ter->tileSel=ter->nbrTile-1;
                }
                else if(event.button.x>ter->decalageX)
                {
                    i=((event.button.y/TILE_HAUTEUR)*(TAILLE_CARTE/TILE_LARGEUR)+event.button.x/TILE_LARGEUR)-8;

                    if(i>=TAILLE_CARTE) i=TAILLE_CARTE-1;
                    setCarte(ter, i, ter->tileSel);
                }
            }
            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                if(event.button.x<ter->decalageX)
                {
                    i=((event.button.y/TILE_HAUTEUR)*(ter->decalageX/TILE_LARGEUR)+event.button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTile;
                   setCollision(&ter->tabChipset[i], (ter->tabChipset[i].collision+1)%2);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
        affChipset(ter, ecran);
        affCarte(ter, ecran);
    }
}

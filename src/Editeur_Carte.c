#include "stdlib.h"
#include "assert.h"
#include "terrain.h"

#define TAILLE 700
#define TAILLE_CARTE 480

int main( int argc, char** argv )
{

    Terrain terrain;
    SDL_Surface* ecran = NULL;

    initTerrain(&terrain);
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(TAILLE, TAILLE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    remplirTerrain(&terrain);

    affChipset(&terrain, ecran);
    affCarte(&terrain, ecran);

    int continuer = 1;
    SDL_Event* event;

    while (continuer)
    {
        SDL_WaitEvent(event);
        switch(event->type)
        {
            case SDL_KEYDOWN:
            { if(event->key.state==SDL_PRESSED)
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
                  /*  else */if(event->key.keysym.sym==SDLK_PAGEUP)
                    {
                        terrain.defilY-=terrain.decalageX/TILE_LARGEUR;
                    }
                    else if(event->key.keysym.sym==SDLK_PAGEDOWN)
                    {
                        terrain.defilY+=terrain.decalageX/TILE_LARGEUR;
                    }
            /* FONCTION SPECIALES */
                    /*else if(event->key.keysym.sym==SDLK_f) /* FILL */
                /* {
                        for(i=0;i<map->width;i++)
                        for(j=0;j<map->height;j++)
                        GET_TILE(i,j,map)=map->tile_sel;
                    }
                    else if(event->key.keysym.sym==SDLK_s) /* SAVE */
                    /*{
                        SaveMap(terrain, "terrain\\save.map", "tiles\\mchip0.bmp");
                    }
                    else if(event->key.keysym.sym==SDLK_l) /* LOAD */
                    /*{
                        f=fopen("map\\save.map","r");
                        if(f)
                        {
                            fclose(f);
                            FreeMap(map);
                            InitMap(map);
                            LoadMap(map, "map\\save.map");
                        }
                    } */ }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event->button.button==SDL_BUTTON_LEFT)
            {
                if(event->button.x<terrain.decalageX)
                {   terrain.tile_sel=((event->button.y/TILE_HAUTEUR)*(terrain.decalageX/TILE_LARGEUR)+event->button.x/TILE_LARGEUR+terrain.defilY)%terrain.nbrTile;
                    if(terrain.tile_sel>=terrain.nbrTile) terrain.tile_sel=terrain.nbrTile-1;
                }
                else if(event->button.x>terrain.decalageX)
                { int i;
                    i=((event->button.y/TILE_HAUTEUR)*(TAILLE_CARTE/TILE_LARGEUR)+event->button.x/TILE_LARGEUR)-8;

                    if(i>=TAILLE_CARTE) i=TAILLE_CARTE-1;
                    setTileCarte(&terrain, i, terrain.tile_sel);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
        affChipset(&terrain, ecran);
        affCarte(&terrain, ecran);
    }


   detruitTerrain(&terrain);
//   free(terrain);
    SDL_Quit();

    return 0;
}

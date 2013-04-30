#include "SDL/SDL.h"
#include "terrain.h"
#include "tile.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

#define TILE_LARGEUR  16
#define TILE_HAUTEUR 16
#define TAILLE_CARTE 480
#define TAILLE_CHIPSET 96

void initTerrain(Terrain* ter)
{
    ter=(Terrain*)malloc(sizeof(Terrain));
//    ter->tabChipset=(Tile*)malloc(sizeof(Tile));
    ter->carte=(unsigned int*)malloc(sizeof(int));
    ter->chipset=NULL;

    ter->defilY=0;
    ter->nbrTile=0;
    ter->largeur=0;
    ter->hauteur=0;
    ter->decalageX=0;
 }

void remplirTerrain(Terrain* ter)
{
    unsigned int i;
    int x = 0;
    int y = 0;
//    ter=(Terrain*)malloc(sizeof(Terrain));
    ter->chipset=SDL_LoadBMP("HOTEL02.bmp");
    ter->hauteur = ter->chipset->h/TILE_HAUTEUR;
    ter->largeur = ter->chipset->w/TILE_LARGEUR;
    setNbrTile(ter, ter->hauteur*ter->largeur);
    ter->decalageX=TILE_LARGEUR*7;
    ter->defilY=0;
    ter->tabChipset=(Tile*)malloc(ter->nbrTile*sizeof(Tile));

    for(i=0;i<getNbrTile(ter); i++ )
    {
        setPosX(&(ter->tabChipset[i]),x);
        setPosY(&(ter->tabChipset[i]),y);

        x +=TILE_LARGEUR;
        if(x>=ter->chipset->w)
        {
            y += TILE_HAUTEUR;
            x= 0;
            }
    }
    ter->carte=(unsigned int*)malloc(TAILLE_CARTE*sizeof(int));
    for(i=0;i<TAILLE_CARTE; i++ )
    {
        ter->carte[i]=0;
    }

}

int getNbrTile(Terrain* ter)
{
    return ter->nbrTile;
}

Tile* getTabChipset(Terrain* ter)
{
    return ter->tabChipset;
}

SDL_Surface* getChipset(Terrain * ter)
{
    return ter->chipset;
}

void setNbrTile(Terrain* ter, int nbrTile)
{
    ter->nbrTile=nbrTile;
}

void setTabChipset(Terrain* ter)
{


}

void setChipset(Terrain* ter)
{

}

int getTileCarte(Terrain* ter, int i)
{
    return ter->carte[i];
}


void setTileCarte(Terrain* ter, int i, int tile_sel)
{
    ter->carte[i]=tile_sel;
}
/*
void sauvegardeTerrain(Terrain* ter)
{
     FILE *f;
     int i,x;
     char buffer[256];

     if(!ter) return;
     f=fopen(filename,"wb");
     if(!f) return;

     memset(&buffer,0,sizeof(buffer));
     strcpy(buffer,chipset);
     fwrite(&buffer,255,sizeof(char),f);

     fwrite(&ter->nbrTile,1,sizeof(unsigned int),f);
     fwrite(&ter->largeur,1,sizeof(unsigned int),f);
     fwrite(&ter->hauteur,1,sizeof(unsigned int),f);
     fwrite(&ter->decalageX,1,sizeof(unsigned int),f);
     fwrite(&ter->defilY,1,sizeof(unsigned int),f);

     for(i=0;i<ter->nbrTile;i++)
     {
        fwrite(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),f);
        fwrite(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),f);
        fwrite(&ter->tabChipset[i].collision, 1, sizeof(unsigned char),f);
    }

     for(x=0;x<TAILLE_CARTE;x++)
        fwrite(&getTileCarte(ter,x), 1, sizeof(unsigned int),f);
     fclose(f);
}


void chargeTerrain(Terrain* ter)
{
    FILE *f;
    int i,x;
    char buffer[256];

    if(!ter) return;
    f=fopen(filename,"wb");
    if(!f) return;

    memset(&buffer,0,sizeof(buffer));
    fread(&buffer,255,sizeof(char),f);
    ter->chipset=SDL_LoadBMP(buffer);
    SDL_SetColorKey(ter->chipset, SDL_SRCCOLORKEY, SDL_MapRGB(ter->chipset->format,8,33,82));


     fread(&ter->nbrTile,1,sizeof(unsigned int),f);
     fread(&ter->largeur,1,sizeof(unsigned int),f);
     fread(&ter->hauteur,1,sizeof(unsigned int),f);
     fread(&ter->decalageX,1,sizeof(unsigned int),f);
     fread(&ter->defilY,1,sizeof(unsigned int),f);

    ter->tabChipset=(Tile*)malloc((ter->nbrTile)*sizeof(Tile));

     for(i=0;i<ter->nbrTile;i++)
     {
        fread(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),f);
        fread(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),f);
        fread(&ter->tabChipset[i].collision, 1, sizeof(unsigned char),f);
    }

     for(x=0;x<TAILLE_CARTE;x++)
        fread(&getTileCarte(ter,x), 1, sizeof(unsigned int),f);
     fclose(f);

     ter->carte =(unsigned int*) malloc(ter->largeur*ter->hauteur*sizeof(unsigned int));

     for(x=0;x<TAILLE_CARTE;x++)
        {
           fread(&getTileCarte(ter, x), 1, sizeof(unsigned int),f);
           if(getTileCarte(ter, x)>=ter->nbrTile)
           {
              fprintf(stderr,"Carte corrompue! (%d)\n",x);
              setTileCarte(ter,x)=0;
           }
        }
}*/

void affChipset(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    unsigned int j;

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;


    /* for(i=0; i<ter->hauteur; i++)
    {  for(j=0;j<ter->largeur; j++)
        {
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
            tile.x=getPosX(ter->tabChipset[(i+ter->defilY)%ter->nbrTile]);
            tile.y=getPosY(ter->tabChipset[(i+ter->defilY)%ter->nbrTile]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

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

void event(Terrain* ter, SDL_Surface* ecran)
{

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
                    /*else */if(event->key.keysym.sym==SDLK_PAGEUP)
                    {
                        ter->defilY-=ter->decalageX/TILE_LARGEUR;
                    }
                    else if(event->key.keysym.sym==SDLK_PAGEDOWN)
                    {
                        ter->defilY+=ter->decalageX/TILE_LARGEUR;
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
                    }*/}
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event->button.button==SDL_BUTTON_LEFT)
            {
                if(event->button.x<ter->decalageX)
                {   ter->tile_sel=((event->button.y/TILE_HAUTEUR)*(ter->decalageX/TILE_LARGEUR)+event->button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTile;
                    if(ter->tile_sel>=ter->nbrTile) ter->tile_sel=ter->nbrTile-1;
                }
                else if(event->button.x>ter->decalageX)
                { int i;
                    i=((event->button.y/TILE_HAUTEUR)*(TAILLE_CARTE/TILE_LARGEUR)+event->button.x/TILE_LARGEUR)-8;

                    if(i>=TAILLE_CARTE) i=TAILLE_CARTE-1;
                    setTileCarte(ter, i, ter->tile_sel);
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

void detruitTerrain(Terrain* ter)
{
    ter->largeur=0;
    ter->hauteur=0;
    ter->nbrTile=0;

    SDL_FreeSurface(ter->chipset);
//    free(ter->tabChipset);
//    free(ter->carte);
//    free(ter);

}


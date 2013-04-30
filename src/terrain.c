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
    ter->tabChipset=NULL;
    ter->carte=NULL;
    ter->chipset=NULL;

    ter->defilY=0;
    ter->nbrTile=0;
    ter->largeur=0;
    ter->hauteur=0;
    ter->decalageX=0;
    ter->tileSel=0;
 }

void remplirStructTerrain(Terrain* ter)
{
    unsigned int i;
    int x = 0;
    int y = 0;
    ter->chipset=SDL_LoadBMP("HOTEL02.bmp");
    setHauteur(ter, ter->chipset->h/TILE_HAUTEUR);
    setLargeur(ter, ter->chipset->w/TILE_LARGEUR);
    setNbrTile(ter, ter->hauteur*ter->largeur);
    setDecalageX(ter,TILE_LARGEUR*7);

// On remplit tabChipset avec les différentes tiles du chipset
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

    // On crée la carte
    ter->carte=(unsigned int*)malloc(TAILLE_CARTE*sizeof(int));
    for(i=0;i<TAILLE_CARTE; i++ )
    {
        setCarte(ter,i, 0);
    }
}

void setNbrTile(Terrain* ter, int nbrTile)
{
    ter->nbrTile=nbrTile;
}

void setDecalageX(Terrain* ter, int x)
{
    ter->decalageX=x;
}

void setDefilY(Terrain* ter, int y)
{
    ter->defilY=y;
}

void setTileSel(Terrain*ter, int selec)
{
    ter->tileSel=selec;
}

void setHauteur(Terrain* ter, unsigned int hauteur)
{
    ter->hauteur=hauteur;
}

void setLargeur(Terrain* ter, unsigned int largeur)
{
    ter->largeur=largeur;
}

void setTabChipset(Terrain* ter, int i, Tile* tile)
{
    ter->tabChipset[i]=*tile;
}

void setCarte(Terrain *ter, int i, int numTile)
{
    ter->carte[i]=numTile;
}

int getNbrTile(Terrain* ter)
{
    return ter->nbrTile;
}

int getDecalageX(Terrain* ter)
{
    return ter->decalageX;
}

int getDefilY(Terrain* ter)
{
    return ter->defilY;
}

int getTileSel(Terrain* ter)
{
    return ter->tileSel;
}

unsigned int getHauteur(Terrain* ter)
{
    return ter->hauteur;
}

unsigned int getLargeur(Terrain* ter)
{
    return ter->largeur;
}

Tile* getTabChipset(Terrain* ter, int i)
{
    return &ter->tabChipset[i];
}

int getCarte(Terrain *ter, int i)
{
    return ter->carte[i];
}

void sauvTerrain(Terrain* ter, char* nomFichier, char* nomChipset)
{
     FILE *fichier;
     int i,x;
     char buffer[256];

     if(!ter) return;
     fichier=fopen(nomFichier,"w");
     if(!fichier) return;

     memset(&buffer,0,sizeof(buffer));
     strcpy(buffer,nomChipset);
     fwrite(&buffer,255,sizeof(char),fichier);

     fwrite(&ter->nbrTile,1,sizeof(unsigned int),fichier);
     fwrite(&ter->largeur,1,sizeof(unsigned int),fichier);
     fwrite(&ter->hauteur,1,sizeof(unsigned int),fichier);
     fwrite(&ter->decalageX,1,sizeof(unsigned int),fichier);
     fwrite(&ter->defilY,1,sizeof(unsigned int),fichier);

     for(i=0;i<ter->nbrTile;i++)
     {
        fwrite(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),fichier);
        fwrite(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),fichier);
        fwrite(&ter->tabChipset[i].collision, 1, sizeof(unsigned char),fichier);
    }

     for(x=0;x<TAILLE_CARTE;x++){
        fwrite(&ter->carte[x], 1, sizeof(unsigned int),fichier);}
     fclose(fichier);
}


void chargeTerrain(Terrain* ter, char* nomFichier)
{
    FILE *fichier;
    int i,x;
    char buffer[256];

    if(!ter) return;
    fichier=fopen(nomFichier,"r");
    if(!fichier) return;

    memset(&buffer,0,sizeof(buffer));
    fread(&buffer,255,sizeof(char),fichier);
    ter->chipset=SDL_LoadBMP(buffer);
    SDL_SetColorKey(ter->chipset, SDL_SRCCOLORKEY, SDL_MapRGB(ter->chipset->format,2,117,118));


     fread(&ter->nbrTile,1,sizeof(unsigned int),fichier);
     fread(&ter->largeur,1,sizeof(unsigned int),fichier);
     fread(&ter->hauteur,1,sizeof(unsigned int),fichier);
     fread(&ter->decalageX,1,sizeof(unsigned int),fichier);
     fread(&ter->defilY,1,sizeof(unsigned int),fichier);

    ter->tabChipset=(Tile*)malloc((ter->nbrTile)*sizeof(Tile));

     for(i=0;i<ter->nbrTile;i++)
     {
        fread(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),fichier);
        fread(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),fichier);
        fread(&ter->tabChipset[i].collision, 1, sizeof(unsigned char),fichier);
    }

     ter->carte =(unsigned int*) malloc(ter->largeur*ter->hauteur*sizeof(unsigned int));

     for(x=0;x<TAILLE_CARTE;x++)
        {
           fread(&ter->carte[x], 1, sizeof(unsigned int),fichier);
           if(getCarte(ter, x)>=ter->nbrTile)
           {
              fprintf(stderr,"Carte corrompue! (%d)\n",x);
              setCarte(ter,x, 0);
           }
        }
}

void detruitTerrain(Terrain* ter)
{
    setNbrTile(ter,0);
    setHauteur(ter,0);
    setLargeur(ter,0);
    setDefilY(ter,0);
    setDecalageX(ter,0);

    SDL_FreeSurface(ter->chipset);
    free(ter->tabChipset);
    free(ter->carte);
}


#include "terrain.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void terInit(Terrain* ter)
{
    ter->tabChipset=NULL;
    ter->carte=NULL;
    ter->chipset=NULL;

    ter->defilY=0;
    ter->nbrTileChipset=0;
    ter->largeurChipset=0;
    ter->hauteurChipset=0;
    ter->decalageX=0;
    ter->tileSel=0;
 }

void terRemplirStruct(Terrain* ter)
{
    unsigned int i;
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int j=0;
    ter->chipset=SDL_LoadBMP("data/Chipsets/desertChipset.bmp");
    setHauteur(ter, ter->chipset->h/TILE_HAUTEUR);
    setLargeur(ter, ter->chipset->w/TILE_LARGEUR);
    setNbrTile(ter, ter->hauteurChipset*ter->largeurChipset);
    setDecalageX(ter,4);

/** On remplit tabChipset avec les différentes tiles du chipset*/
    ter->tabChipset=(Tile*)malloc(ter->nbrTileChipset*sizeof(Tile));
    for(i=0/TILE_LARGEUR;i<getNbrTile(ter); i++ )

    {
            setPosX(&ter->tabChipset[i],x);
            setPosY(&ter->tabChipset[i],y);

            x +=TILE_LARGEUR;

            if(x>=ter->decalageX*TILE_LARGEUR+j)
                {
                    y += TILE_HAUTEUR;
                    if(y>=ter->hauteurChipset*TILE_HAUTEUR)
                    {
                        y=0;
                        j+=ter->decalageX*TILE_LARGEUR;
                    }
                    x=j;
                }
    }
    /** On crée la carte*/
    ter->carte=(unsigned int*)malloc(CARTE_HAUTEUR*CARTE_LARGEUR*sizeof(unsigned int));
    for(i=0;i<CARTE_HAUTEUR*CARTE_LARGEUR; i++ )
    {
        setCarte(ter,i, 0);
    }
}

void setNbrTile(Terrain* ter, unsigned int nbrTile)
{
    ter->nbrTileChipset=nbrTile;
}

void setDecalageX(Terrain* ter, int x)
{
    ter->decalageX=x;
}

void setDefilY(Terrain* ter, int y)
{
    ter->defilY=y;
}

void setTileSel(Terrain*ter, unsigned int selec)
{
    ter->tileSel=selec;
}

void setHauteur(Terrain* ter, unsigned int hauteur)
{
    ter->hauteurChipset=hauteur;
}

void setLargeur(Terrain* ter, unsigned int largeur)
{
    ter->largeurChipset=largeur;
}

void setTabChipset(Terrain* ter, int i, Tile* tile)
{
    ter->tabChipset[i]=*tile;
}

void setCarte(Terrain *ter, int i, unsigned int numTile)
{
    ter->carte[i]=numTile;
}

unsigned int getNbrTile(Terrain* ter)
{
    return ter->nbrTileChipset;
}

int getDecalageX(Terrain* ter)
{
    return ter->decalageX;
}

int getDefilY(Terrain* ter)
{
    return ter->defilY;
}

unsigned int getTileSel(Terrain* ter)
{
    return ter->tileSel;
}

unsigned int getHauteur(Terrain* ter)
{
    return ter->hauteurChipset;
}

unsigned int getLargeur(Terrain* ter)
{
    return ter->largeurChipset;
}

Tile* getTabChipset(Terrain* ter, int i)
{
    return &ter->tabChipset[i];
}

int getCarte(Terrain *ter, int i)
{
    return ter->carte[i];
}

void terSauvegarde(Terrain* ter, char* nomFichier, char* nomChipset)
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

     fwrite(&ter->nbrTileChipset,1,sizeof(unsigned int),fichier);
     fwrite(&ter->largeurChipset,1,sizeof(unsigned int),fichier);
     fwrite(&ter->hauteurChipset,1,sizeof(unsigned int),fichier);
     fwrite(&ter->decalageX,1,sizeof(int),fichier);
     fwrite(&ter->defilY,1,sizeof(int),fichier);

     for(i=0;i<ter->nbrTileChipset;i++)
     {
        fwrite(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),fichier);
        fwrite(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),fichier);
        fwrite(&ter->tabChipset[i].collision, 1, sizeof( char),fichier);
    }

     for(x=0;x<CARTE_HAUTEUR*CARTE_LARGEUR; x++){
        fwrite(&ter->carte[x], 1, sizeof(unsigned int),fichier);}
     fclose(fichier);
}


void terCharger(Terrain* ter, char* nomFichier)
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
/*    SDL_SetColorKey(ter->chipset, SDL_SRCCOLORKEY, SDL_MapRGB(ter->chipset->format,2,117,118));*/


     fread(&ter->nbrTileChipset,1,sizeof(unsigned int),fichier);
     fread(&ter->largeurChipset,1,sizeof(unsigned int),fichier);
     fread(&ter->hauteurChipset,1,sizeof(unsigned int),fichier);
     fread(&ter->decalageX,1,sizeof(int),fichier);
     fread(&ter->defilY,1,sizeof(int),fichier);

    ter->tabChipset=(Tile*)malloc((ter->nbrTileChipset)*sizeof(Tile));

     for(i=0;i<ter->nbrTileChipset;i++)
     {
        fread(&ter->tabChipset[i].posX, 1, sizeof(unsigned int),fichier);
        fread(&ter->tabChipset[i].posY, 1, sizeof(unsigned int),fichier);
        fread(&ter->tabChipset[i].collision, 1, sizeof(char),fichier);
    }

     ter->carte =(unsigned int*) malloc(CARTE_HAUTEUR*CARTE_LARGEUR*sizeof(unsigned int));

     for(x=0;x<CARTE_HAUTEUR*CARTE_LARGEUR;x++)
        {
           fread(&ter->carte[x], 1, sizeof(unsigned int),fichier);
           if(getCarte(ter, x)>=ter->nbrTileChipset)
           {
              fprintf(stderr,"Carte corrompue! (%d)\n",x);
              setCarte(ter,x, 0);
           }
        }
}

void terLibere(Terrain* ter)
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


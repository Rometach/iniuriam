#include "liste_perso.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/


void listePersoInit(Liste_Perso* liste, int nbr,char numCarte)
{
    int i;
    liste->nbrPerso=nbr;
    liste->perso =(Personnage*)malloc(nbr*sizeof(Personnage));

    for(i=0; i<nbr;i++)
    {
        persoInit(&liste->perso[i]);
    }
    liste->numCarte=numCarte;
}

void tabListePersoInit(Liste_Perso* liste, int nbr)
{
    liste=(Liste_Perso*)malloc(nbr*sizeof(Liste_Perso));
}

int getNbrPerso(Liste_Perso* liste)
{
    return liste->nbrPerso;
}

void setNbrPerso(Liste_Perso* liste, int i)
{
    liste->nbrPerso=i;
}

Personnage* getPerso(Liste_Perso liste, int i)
{
    return (Personnage*)&liste.perso[i];
}

char getListeNumCarte(Liste_Perso* liste)
{
    return liste->nbrPerso;
}

int testCollisionPerso(Personnage* hero, Liste_Perso* pnj, int nbPnj, int direction)
{
   int i;
   for(i=0; i<nbPnj; i++)
    {
    if(((getPersoPosX(hero)+TILE_LARGEUR)==getPersoPosX(pnj[i].perso) && getPersoPosY(hero)==getPersoPosY(pnj[i].perso))
        || ((getPersoPosX(hero)-TILE_LARGEUR)==getPersoPosX(pnj[i].perso) && getPersoPosY(hero)==getPersoPosY(pnj[i].perso))
        || ((getPersoPosY(hero)+TILE_HAUTEUR)==getPersoPosY(pnj[i].perso) && getPersoPosX(hero)==getPersoPosX(pnj[i].perso))
        || ((getPersoPosY(hero)-TILE_HAUTEUR)==getPersoPosY(pnj[i].perso) && getPersoPosX(hero)==getPersoPosX(pnj[i].perso)))
        {
           switch(direction)
            {
                case 1: if((getPersoPosX(hero)+TILE_LARGEUR)==getPersoPosX(pnj[i].perso) && getPersoPtDeVie(pnj[i].perso)>0) return i;
                break;

                case 2: if((getPersoPosX(hero)-TILE_LARGEUR)==getPersoPosX(pnj[i].perso) && getPersoPtDeVie(pnj[i].perso)>0) return i;
                break;

                case 3: if((getPersoPosY(hero)+TILE_HAUTEUR)==getPersoPosY(pnj[i].perso) && getPersoPtDeVie(pnj[i].perso)>0) return i;
                break;

                case 4: if((getPersoPosY(hero)-TILE_HAUTEUR)==getPersoPosY(pnj[i].perso) && getPersoPtDeVie(pnj[i].perso)>0) return i;
                break;
            }
        }
    }
   return -1;
return 0;
}

void listePersoLibere(Liste_Perso* liste)
{
    int i;
    for(i=0; i<liste->nbrPerso; i++)
    {
        persoLibere(&liste->perso[i]);
    }
    liste->nbrPerso=0;
    liste->numCarte=0;
}

void tabListePersoLibere(Liste_Perso* liste)
{
    free(liste->perso);
}

int getNbGroupesPNJ()
{
    int max=0;
    FILE* fPNJ;
    char ligne[TAILLE_MAX_FICHIER];

    assert(fPNJ=fopen("data/PNJ.txt","r"));
    if (fPNJ!=NULL)
    {
        do
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fPNJ);
            max++;
        }while (ligne[0]!='/'&&ligne[1]!='/');
    }
    fclose(fPNJ);

    assert(max%3==0);

    return ((max-3)/3);
}

void initialiserTousLesPNJ2(Liste_Perso** tabPNJ, Objet* tabObjets)
{
    int i, j, max, nbDansGroupe, numeroPerso,numCarte;
    char ligne[TAILLE_MAX_FICHIER];
    FILE* fGroupes;

    max = getNbGroupesPNJ();
    (*tabPNJ)=(Liste_Perso*)malloc(max*sizeof(Liste_Perso));

    assert(fGroupes=fopen("data/GroupesPNJ.txt", "r"));

    /*On saute les 3 premières lignes du fichier*/
    for(i=0;i<3;i++)
    {
        fgets(ligne, TAILLE_MAX_FICHIER, fGroupes);
    }


    for(i=0;i<max;i++)
    {
        fscanf(fGroupes, "%d/%d\n", &nbDansGroupe,&numCarte);
        (((*tabPNJ)[i]).perso) = (Personnage*) malloc(nbDansGroupe*sizeof(Personnage));
        (((*tabPNJ)[i]).nbrPerso) = nbDansGroupe;
        (((*tabPNJ)[i]).numCarte) = (char)numCarte;
        for(j=0;j<nbDansGroupe;j++)
        {
            fscanf(fGroupes, "%d ", &numeroPerso);
            persoInitPNJ( &((((*tabPNJ)[i]).perso)[j]) , numeroPerso, tabObjets) ;
        }
        fscanf(fGroupes, "\n");
        fgets(ligne, TAILLE_MAX_FICHIER, fGroupes);
    }
}

void libererTousLesPNJ2(Liste_Perso** tabPNJ)
{
    int i, max;

    max = getNbGroupesPNJ();

    for(i=0;i<max;i++)
    {
        free(((*tabPNJ)[i]).perso);
    }

    free(*tabPNJ);

}

void copieListe_Perso(Liste_Perso* liste1, Liste_Perso* liste2)
{
    copiePerso(liste1->perso,liste2->perso);
    liste1->nbrPerso=liste2->nbrPerso;
    liste1->numCarte=liste2->numCarte;
}

int getPNJCarte(Liste_Perso** tabPNJ,char numCarte)
{
    int i,j=0,max;
    max = getNbGroupesPNJ();

    for (i=0;i<max;i++)
    {
        if (((*tabPNJ)[i]).numCarte==numCarte)
        {
            copieListe_Perso(&((*tabPNJ)[j]),&((*tabPNJ)[i]));
            j++;
        }
    }
    for(i=j;i<max;i++)
    {
        free(((*tabPNJ)[i]).perso);
    }
    return j;
}


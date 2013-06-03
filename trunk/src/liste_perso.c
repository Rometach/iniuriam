#include "liste_perso.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/


void listePersoInit(Liste_Perso* liste, int nbr)
{
    int i;
    liste->nbrPerso=nbr;
    liste->perso =(Personnage*)malloc(nbr*sizeof(Personnage));

    for(i=0; i<nbr;i++)
    {
        persoInit(&liste->perso[i]);
    }

}

void tabListePerso(Liste_Perso* liste, int nbr)
{
    liste=(Liste_Perso*)malloc(nbr*sizeof(Liste_Perso));
}

void tabListePersoInitPNJ(Liste_Perso* liste, Objet* tabObjets)
{
    int i;
    int max = getNbPNJ();

    for(i=1;i<=max;i++)
        {
            listePersoInit(&liste[i-1], 1);
            persoInitPNJ(liste[i-1].perso,i,tabObjets);
        }
}

int getNbrPerso(Liste_Perso* liste)
{
    return liste->nbrPerso;
}

void setNbrPerso(Liste_Perso* liste, int i)
{
    liste->nbrPerso=i;
}

void listePersoLibere(Liste_Perso* liste)
{
    int i;
    for(i=0; i<liste->nbrPerso; i++)
    {
        persoLibere(&liste->perso[i]);
    }
    liste->nbrPerso=0;
}

void tabListePersoLibere(Liste_Perso* liste)
{
    free(liste);
}

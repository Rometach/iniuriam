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
    int i, j, max, nbDansGroupe, numeroPerso;
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
            fscanf(fGroupes, "%d\n", &nbDansGroupe);
            (((*tabPNJ)[i]).perso) = (Personnage*) malloc(nbDansGroupe*sizeof(Personnage));
            (((*tabPNJ)[i]).nbrPerso) = nbDansGroupe;

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




















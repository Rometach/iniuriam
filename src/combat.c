#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "personnage.h"
#include "terrain.h"
#include "deplacement.h"
#include "combat.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 22
#define NB_DEPLACEMENTS 5

void areneInit (Terrain* terrain, char tab[TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0; i<TAILLE_MAX;i++)
    {
        for (j=0;j<TAILLE_MAX;j++)
        {
            tab[i][j]=terrain->tabChipset[i*TAILLE_MAX+j].collision;
        }
    }
}

char tri (char* tab, char e, int l)
{
    int i,j;
    for (i=0;i<l;i++)
    {
       if (e>tab[i])
       {
           for (j=l;j>i;j--)
           {
               tab[j]=tab[j-1];
           }
           tab[i]=e;
           return i;
       }
    }
    tab[l]=e;
    return l;
}

void initCombattant (Personnage* liste, int l, Combattant* groupe)
{
    int i,j;
    char tab [l];
    for (i=0;i<l;i++)
    {
        groupe[i].perso=(&liste[i]);
        groupe[i].camp=getPersoFaction(&liste[i]);
        for (j=0;j<=i;j++)
        {
            groupe[i].ordre=tri(tab, getPersoAgilite(&liste[i]),i);
        }
    }
}

void initPosGauche (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i=1,j=1;
    char colonne [TAILLE_MAX], place=0;
    while ((place==0)&&(i<TAILLE_MAX))
    {
        getColonne(i,arene,colonne);
        while ((place==0)&&(j<TAILLE_MAX))
        {
            if (deplacerCase(j,colonne)!=0)
            {
                arene[i][j]=4;
                combattant->posX=i;
                combattant->posY=j;
                combattant->orientation=3;
                place=1;
            }
            j+=2;
        }
        i+=2;
    }
    if (place==0)
    {
        char nom [40];
        getPersoNom(nom,combattant->perso);
        printf ("Impossible de placer %s\n", nom);
    }

}

void initPosDroite (Combattant* combattant, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i=TAILLE_MAX-2,j=TAILLE_MAX-2;
    char colonne [TAILLE_MAX], place=0;
    while ((place==0)&&(i>0))
    {
        getColonne(i,arene,colonne);
        while ((place==0)&&(j>0))
        {
            if (deplacerCase(j,colonne)!=0)
            {
                arene[i][j]=4;
                combattant->posX=i;
                combattant->posY=j;
                combattant->orientation=1;
                place=1;
            }
            j-=2;
        }
        i-=2;
    }
    if (place==0)
    {
        char nom [40];
        getPersoNom(nom,combattant->perso);
        printf ("Impossible de placer %s\n", nom);
    }
}

void initPosCombattant (Combattant*liste, int l, char arene[TAILLE_MAX][TAILLE_MAX])
{
    int i;
    for (i=0;i<l;i++)
    {
        if (liste[i].camp==liste[0].camp) initPosGauche (&liste[i], arene);
        else initPosDroite (&liste[i],arene);
    }
}

void ordreGroupe (Combattant* liste, int l)
{
    int i;
    Combattant tampon;
    for (i=0; i<l-1; i++)
    {
        if (liste[i].ordre>liste[i+1].ordre)
        {
            tampon=liste[i];
            liste[i]=liste[i+1];
            liste[i+1]=tampon;
        }
    }
}

void combatInit (Personnage* liste, Terrain* terrain, int l, Combattant* groupe, char arene [TAILLE_MAX][TAILLE_MAX])
{
    areneInit (terrain, arene);
    initCombattant (liste, l, groupe);
    initPosCombattant (groupe, l, arene);
    ordreGroupe (groupe, l);
}

char estDansChampDeVision (char arene[TAILLE_MAX][TAILLE_MAX], int x, int y, int z, int t,char orientation)
{
    int i,j,a,b,c,d,rayon=10;
    char vu=0;
    if (rayon*rayon>=(z-x)*(z-x)+(t-y)*(t-y))
    {
        switch (orientation)
        {
            case 1: a=max(x-rayon,1);
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=max(y-rayon,1);
                    d=y;
                    break;
            case 2: a=max(x-rayon,1);
                    b=x;
                    c=max(y-rayon,1);
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            case 3: a=max(x-rayon,1);
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=y;
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            case 4: a=x;
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=max(y-rayon,1);
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            default: break;
        }
        for (i=a;i<b;i++)
        {
            for (j=c;j<d;j++)
            {
                if (((j-y)*(j-y)+(i-x)*(i-x)<=rayon*rayon))
                {
                    if (i==z&&j==t) vu=1;
                    else if (i==x&&j==y){}
                    else if (i==x)
                    {
                        if (deplacerCase(j,arene[i])==0) return 0;
                    }
                    else if (deplacerCase(j,arene[i])==0)
                    {
                        if ((int)((j-y)/(i-x)*z)==t)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        if (vu==1)
        {
            return 1;
        }
    }
    else return 0;
    return 0;
}

char estLaFin (Combattant* groupe,int l)
{
    int i;
    if (l==1) return 1;
    else
    {
        for (i=1;i<l;i++)
        {
            if (groupe[i].camp!=groupe[0].camp) return 0;
        }
    }
    return 1;
}

int testNbCombattant (Combattant* groupe, int l)
{
    Combattant* tampon;
    int i,j,n=l;
    for (i=0;i<l;i++)
    {
        if (groupe[i].perso->ptDeVie==0)
        {
            n--;
            tampon=(Combattant*)malloc((n)*sizeof(Combattant));
            for (j=0;j<l-1;j++)
            {
                if (i!=j) tampon[j]=groupe[j];
            }
            free (groupe);
            groupe=tampon;

        }
    }
    return n;
}

void tourIA (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i, cible=j,arme=0;
    char distance=255, degats=0,tampon, arene2[TAILLE_MAX][TAILLE_MAX];

    for (i=0;i<l;i++)
    {
        if ((i!=j)&&(groupe[j].camp!=groupe[i].camp)&&(estDansChampDeVision(arene,groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,groupe[j].orientation)))
        {
            tampon=deplacementIA(groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,arene);
            if (tampon!=0)
            {
                if (tampon==min(distance,tampon))
                {
                    distance=tampon;
                    cible=i;
                }
            }
        }
    }
    if (cible!=j)
    {
        for (i=0;i<groupe[j].perso->inventaire.nbObjet;i++)
        {
            if (getObjetPortee(getStockObjet(groupe[j].perso->inventaire.st))>=distance)
            {
                tampon=getObjetDegats(getStockObjet(groupe[j].perso->inventaire.st));
                if (tampon==max(tampon,degats))
                {
                    arme=i;
                    degats=tampon;
                }
            }
        }
        if (arme!=0)
        {
            /*CHAAAAAAARGEEEEEZ*/
        }
        else {}
    }
}
void tourJoueur (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{

}

void combat (Combattant* groupe, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i,nb=l;
    while (estLaFin(groupe, nb)!=0)
    {
        for (i=0;i<nb;i++)
        {
            if(groupe[i].camp==groupe[0].camp)
            {
                tourJoueur(groupe,i,l,arene);
                nb=testNbCombattant(groupe,nb);
            }
            else
            {
                tourIA(groupe,i,l,arene);
                nb=testNbCombattant(groupe,nb);
            }
        }
    }
}

int mainCombat ()
{
    Personnage *liste;
    Combattant* groupe;
    int i,j,type=2;
    char arene [TAILLE_MAX][TAILLE_MAX],ligne [TAILLE_MAX+2];
    liste=(Personnage*)malloc(2*sizeof(Personnage));
    groupe=(Combattant*)malloc(2*sizeof(Combattant));
    Objet *tab;
    tab=(Objet*)malloc(40*sizeof(Objet));
    initialiserTousLesObjets(tab);

    persoInit (&liste[0], "Toromis", 1, 1, 1, 1, 0, 100,tab);
    persoInit (&liste[1], "Babar", 2, 1, 2, 1, 0, 100,tab);
    FILE* fTerr=fopen("data/Terrains.txt", "r");
    if (fTerr!=NULL)
    {
        for (i=0; i<4;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<(TAILLE_MAX+2)*(type-1);i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<TAILLE_MAX;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
            for (j=0;j<TAILLE_MAX;j++)
            {
                arene[i][j]=ligne[j]-'0';
            }
        }
        fclose (fTerr);
        initCombattant(liste,2,groupe);
        initPosCombattant(groupe,2,arene);
        ordreGroupe(groupe,2);
        afficherTab2D (arene);
        combat (groupe,2,arene);

    }
    persoLibere(&liste[0]);
    persoLibere(&liste[1]);
    free (liste);
    return 0;
}

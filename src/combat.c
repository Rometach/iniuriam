#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "personnage.h"
#include "terrain.h"
#include "deplacement.h"
#include "combat.h"
#include "inventaire.h"


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
    char *tab = (char*) malloc(l*sizeof(char));
    for (i=0;i<l;i++)
    {
        groupe[i].perso=(&liste[i]);        /*Faire un copier machin svp*/
        groupe[i].camp=getPersoFaction(&liste[i]);
        groupe[i].derniereAction=0;
        for (j=0;j<=i;j++)
        {
            groupe[i].ordre=tri(tab, getPersoAgilite(&liste[i]),i);
        }
    }
    free (tab);
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
                combattant->orientation=4;
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

void initCombat (Personnage* liste, int l, Combattant* groupe, char arene[TAILLE_MAX][TAILLE_MAX])
{
    initCombattant(liste,l,groupe);
    initPosCombattant(groupe,l,arene);
    ordreGroupe(groupe,l);
}


char estDansChampDeVision (char arene[TAILLE_MAX][TAILLE_MAX], int x, int y, int z, int t,char orientation)
{
    int i,j,a,b,c,d,rayon=30;
    char vu=0;
    if (rayon>=(int)sqrt(pow((z-x),2)+pow((t-y),2)))
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
            case 4: a=max(x-rayon,1);
                    b=min(rayon+x,TAILLE_MAX-1);
                    c=y;
                    d=min(y+rayon,TAILLE_MAX-1);
                    break;
            case 3: a=x;
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
                if ((int)sqrt(pow((j-y),2)+pow((i-x),2))<=rayon)
                {
                    if (i==z&&j==t) vu=1;
                    else if (i==x&&j==y){}
                    else if (deplacerCase(j,arene[i])==0)
                    {
                        if (i==x)
                        {
                            if((x==z)&&(fabs(x-i)<fabs(x-z))) return 0;
                        }
                        else if (j==y)
                        {
                            if ((y==t)&&(fabs(i-x)<fabs(i-z))) return 0;
                        }
                        else if ((int)((j-y)/(i-x)*z)==t)
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
    for (i=0;i<n;i++)
    {
        if (groupe[i].perso->ptDeVie<=0)
        {
            n--;
            tampon=(Combattant*)malloc((n)*sizeof(Combattant));
            for (j=l-2;j>=0;j--)
            {
                if (j>i) tampon[j]=groupe[j+1];
                else if (j<i) tampon[j]=groupe[j];
            }
            free (groupe);
            groupe=tampon;
        }
    }
    return n;
}

int attaquer (Personnage* attaquant, Personnage* defenseur, int degats, int bonusA, int bonusD)
{
    int testA, testD;
    int deg=0;

    testA=getPersoAttaque(attaquant)+bonusA-rand()%100;

    if (testA>=0)
    {
        testD=getPersoDefense(defenseur)+bonusD-rand()%100;
        testA=testA-max(testD,0);

        if(testA>=30)
        {
            printf("Coup critique\n");
            deg=4*degats;
        }
        else if(testA>=20)
        {
            printf("Coup qui fait mal\n");
            deg=3*degats;
        }
        else if(testA>=10)
        {
            printf("Beigne\n");
            deg=2*degats;
        }
        else if(testA>=0)
        {
            printf("Touche, mais de justesse\n");
            deg=degats;
        }
        else
        {
            printf("Epic parade.\n");
        }
    }
    else
    {
        printf("Rate.\n");
    }
    addPersoPtDeVie(defenseur, -deg);

    return deg;
}



void tourIA (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i, cible=j, arme=0,coord,rayon;
    char distance=100, degats=0,tampon, arene2[TAILLE_MAX][TAILLE_MAX],deplacementsRestants=NB_DEPLACEMENTS, portee;
    for (i=0;i<l;i++)
    {
        if ((i!=j)&&(groupe[j].camp!=groupe[i].camp)&&(estDansChampDeVision(arene,groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,groupe[j].orientation)!=0))
        {
            copieTab2D(arene,arene2);
            tampon=chemin(groupe[j].posX,groupe[j].posY,groupe[i].posX,groupe[i].posY,arene2);
            if (tampon!=0)
            {
                if (tampon<=distance)
                {
                    copieTab2D (arene2,groupe[j].arene);
                    distance=tampon;
                    cible=i;
                    rayon=(int)(sqrt(pow(groupe[j].posX-groupe[i].posX,2)+pow(groupe[j].posY-groupe[i].posY,2)));
                }
            }
        }
    }
    if (cible!=j)
    {
        for (i=0;i<getInventaireNbObjets(getPersoInventaire2(groupe[j].perso));i++)
        {
            portee=getObjetPortee(getStockObjet(getInventaireStock(getPersoInventaire2(groupe[j].perso),i)));
            if ((rayon>=portee-NB_DEPLACEMENTS-5)&&(rayon<=portee+NB_DEPLACEMENTS))
            {
                tampon=getObjetDegats(getStockObjet(groupe[j].perso->inventaire.st));
                if (tampon>degats)
                {
                    arme=i+1;
                    degats=tampon;
                }
            }
        }
        if (arme!=0)
        {
            portee=getObjetPortee(getStockObjet(getInventaireStock(getPersoInventaire2(groupe[j].perso),arme-1)));
            while (portee<rayon)
            {
                arene[groupe[j].posX][groupe[j].posY]=1;
                coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,1,&(groupe[j].orientation));
                if (coord)
                {
                    groupe[j].posY=coord%TAILLE_MAX;
                    groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                    arene[groupe[j].posX][groupe[j].posY]=4;
                    deplacementsRestants--;
                    rayon=(int)(sqrt(pow(groupe[j].posX-groupe[cible].posX,2)+pow(groupe[j].posY-groupe[cible].posY,2)));
                }
                else printf("Impossible de se rapprocher\n");
            }
            while (portee-5>rayon)
            {
                arene[groupe[j].posX][groupe[j].posY]=1;
                coord=sEloigner(groupe[j].arene,groupe[j].posX,groupe[j].posY,1,&(groupe[j].orientation));
                if (coord)
                {
                    groupe[j].posY=coord%TAILLE_MAX;
                    groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
                    arene[groupe[j].posX][groupe[j].posY]=4;
                    deplacementsRestants--;
                }
                else printf("Impossible de s'écarter\n");
            }
            attaquer(groupe[j].perso,groupe[cible].perso,degats,0,0);
            printf("%d\n",getPersoPtDeVie(groupe[cible].perso));
        }
        else
        {
            arene[groupe[j].posX][groupe[j].posY]=1;
            coord=seRapprocher(groupe[j].arene,groupe[j].posX,groupe[j].posY,NB_DEPLACEMENTS,&(groupe[j].orientation));
            i=coord%TAILLE_MAX;
            if (groupe[j].posY<i)
            {

            }
            groupe[j].posY=coord%TAILLE_MAX;
            groupe[j].posX=(coord-coord%TAILLE_MAX)/TAILLE_MAX;
            arene[groupe[j].posX][groupe[j].posY]=4;
            if (coord==0) printf("Impossible de se rapprocher\n");
        }
    }
    else
    {
        printf("Aucune cible repérée\n");
    }
}


void tourJoueur (Combattant* groupe, int j, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{

}


void combat (Combattant* groupe, int l, char arene [TAILLE_MAX][TAILLE_MAX])
{
    int i,nb=l;
    while (estLaFin(groupe, nb)==0)
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
                afficherTab2D(arene);
                //getchar();
            }
        }
    }
}


int mainCombat ()
{
    Personnage *liste;
    Combattant* groupe;
    Objet *tab;
    int i,j,type=1;
    char arene [TAILLE_MAX][TAILLE_MAX],ligne [TAILLE_MAX+2];

    srand(time(NULL));

    liste=(Personnage*)malloc(4*sizeof(Personnage));
    groupe=(Combattant*)malloc(4*sizeof(Combattant));
    tab=(Objet*)malloc(40*sizeof(Objet));

    initialiserTousLesObjets(tab);

    nouveauPerso (&liste[0], "Toromis", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[1], "Rometach", 1, 1, 1, 1, 0, 100,tab);
    nouveauPerso (&liste[2], "Babar", 2, 1, 2, 1, 0, 100,tab);
    nouveauPerso (&liste[3], "BabarII", 2, 1, 2, 1, 0, 100,tab);

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

        initCombat(liste,4,groupe,arene);
        afficherTab2D (arene);
        combat (groupe,4,arene);

    }
    persoLibere(&liste[0]);
    persoLibere(&liste[1]);
    persoLibere(&liste[2]);
    persoLibere(&liste[3]);
    free (liste);
    free (groupe);
    return 0;
}

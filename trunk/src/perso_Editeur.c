#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "personnage.h"
#include "SDL/SDL.h"
#include "inventaire.h"
#include "capacite.h"
#include "competence.h"
#include "objet.h"
#include "SDL/SDL.h"
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void getPersoNom(char* maChaine, Personnage *perso)
{
    strcpy(maChaine,perso->nom);  /* Courageux, rajoutez un assert */
}


char getPersoRace(Personnage *perso)
{
    return perso->race;
}


char getPersoSexe(Personnage *perso)
{
    return perso->sexe;
}

char getPersoFaction(Personnage *perso)
{
    return perso->faction;
}


void getPersoFactionNom(char* chaine, Personnage *perso)
{
    switch(perso->faction)
    {
        case 1 :
            strcpy(chaine,"Sistéen");
        case 2 :
            strcpy(chaine,"Heredian");
        case 3 :
            strcpy(chaine,"Marchand");
        default :
            strcpy(chaine,"Non défini");
    }
}


char getPersoCarriere(Personnage *perso)
{
    return perso->carriere;
}


void getCarriereNom(char carriere, char* s)
{
    int i;
    FILE* fCarr= fopen("data/Carrieres.txt", "r");
    if(fCarr!=NULL)
    {
        char ligne [TAILLE_MAX_FICHIER];
        for (i=0;i<carriere+3;i++)
        {
           fgets(ligne,TAILLE_MAX_FICHIER,fCarr);
        }
    i= strchr (ligne, '/')-ligne;
    strncpy(s,ligne,i);
    fclose(fCarr);
    }
    else
    {
        printf("Impossible d'ouvrir Carrieres.txt\n");
    }
}


int getPersoArgent(Personnage *perso)
{
    return perso->argent;
}


int getPersoExperience(Personnage *perso)
{
    return perso->experience;
}

char getPersoAttaque(Personnage *perso)
{
    return perso->attaque;
}

char getPersoDefense(Personnage *perso)
{
    return perso->defense;
}

char getPersoIntelligence(Personnage *perso)
{
    return perso->intelligence;
}

char getPersoAgilite(Personnage *perso)
{
    return perso->agilite;
}

char getPersoCharisme(Personnage *perso)
{
    return perso->charisme;
}

int getPersoPtDeVie(Personnage *perso)
{
    return perso->ptDeVie;
}

void setPersoPosX(Personnage *perso, int x)
{
    perso->posX=x;
}

int getPersoPosX(Personnage *perso)
{
    return perso->posX;
}

void setPersoPosY(Personnage *perso, int y)
{
    perso->posY=y;
}

int getPersoPosY(Personnage *perso)
{
    return perso->posY;
}

void setPersoArgent(Personnage *perso, int somme)
{
    perso->argent=somme;
}

void addPersoPtDeVie(Personnage *perso, int pdv)
{
    perso->ptDeVie+=pdv;
}

void addPersoExperience(Personnage *perso, int exp)
{
    perso->experience+=exp;
}

int getPersoNiveau (Personnage* perso)
{
    return 1+perso->experience/10;
}

int getNbPNJ()
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
    return max;
}

void initialiserTousLesPNJ(Personnage* tabPNJ)
{
    int i;
    int max = getNbPNJ();

    //*tabPNJ=(Personnage*)malloc(max*sizeof(Personnage));
        for(i=1;i<max-4;i++)
        {
            /*STILL TO BE DONE*/
        }
}

void libererTousLesPNJ(Personnage* tabPNJ)
{
    free(tabPNJ);
}

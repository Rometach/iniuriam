#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "parole.h"
#include "personnage.h"

#define TAILLE_MAX_DIAL 200

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2)
{
    dialogue->perso1=perso1;
    dialogue->perso2=perso2;
    if (getPersoFaction(perso1)==getPersoFaction(perso2)) /*Les personnages sont alliés*/
    {
        dialogue->humeur=50;
    }
    else if ((getPersoFaction(perso1)==0)&&(getPersoFaction(perso2)==1))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else if ((getPersoFaction(perso1)==1)&&(getPersoFaction(perso2)==0))  /*Les personnages sont ennemis*/
    {
        dialogue->humeur=10;
    }
    else    /*L'un des personnages est marchand...*/
    {
        dialogue->humeur=25;
    }
}



void setDialogueHumeur (Dialogue* dialogue, int hum)
{
    if (hum<0)
    {
        dialogue->humeur=0;
    }
    else if (hum>100)
    {
        dialogue->humeur=100;
    }
    else
    {
        dialogue->humeur=hum;
    }
}



void soudoyer(Dialogue* dialogue, int argent)
{
    setPersoArgent(dialogue->perso1, getPersoArgent(dialogue->perso1)-argent);
    setPersoArgent(dialogue->perso2, getPersoArgent(dialogue->perso2)+argent);

    if(getPersoFaction(dialogue->perso1)==3)  /*C'est plus facile de soudoyer un marchand...*/
    {
        setDialogueHumeur(dialogue, dialogue->humeur+(rand()%((int)(argent/20))));

    }
    else
    {
        setDialogueHumeur(dialogue, dialogue->humeur+(rand()%((int)(argent/100))));
    }
}


void obtenirInfo(Dialogue* dialogue, char* info)
{
    FILE* fDial;
    int i;
    int test;
    char nomPNJ[30];

    getPersoNom(nomPNJ, dialogue->perso2);

    assert(fDial=fopen("data/Dialogues.txt", "r"));


    if (fDial!=NULL)
    {
        test=(rand()%100);
        if(test<(dialogue->humeur))
        {
            strcat(nomPNJ,"\n");
            while((strcmp(nomPNJ,fgets(info,TAILLE_MAX_DIAL,fDial))!=0))     {}
            for(i=0;i<=(rand()%3);i++)  {fgets(info,TAILLE_MAX_DIAL,fDial);}

            printf("\n%s",info);
            setDialogueHumeur(dialogue,dialogue->humeur-5);
        }
        else
        {
            while((strcmp("Refus info\n",fgets(info,TAILLE_MAX_DIAL,fDial))!=0))     {}
            for(i=0;i<=(rand()%3);i++)  {fgets(info,TAILLE_MAX_DIAL,fDial);}

            printf("\n%s",info);
            setDialogueHumeur(dialogue,dialogue->humeur-5);
        }
        fclose(fDial);
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Dialogues.txt");
    }
}



int main(int argc, char** argv)
{
    int k;
    Dialogue dial;
    Personnage perso;
    Personnage pnj;
    char information[TAILLE_MAX_DIAL];

    srand(time(NULL));
    persoInit (&perso, "Toromis", 1, 1, 1, 1, 0, 100);
    persoInit (&pnj, "Babar", 1, 1, 1, 1, 0, 100);
    dialogueInit(&dial,&perso,&pnj);

    for(k=0;k<20;k++)
    {
        obtenirInfo(&dial, information);
    }

    return 0;
}

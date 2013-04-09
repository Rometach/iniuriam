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



char setDialogueHumeur (Dialogue* dialogue, int hum)
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
    return dialogue->humeur;
}



void setReponse (char* question, char* reponse)
{
    FILE* fDial;
    int i;

    assert(fDial=fopen("data/Dialogues.txt", "r"));

    if (fDial!=NULL)
    {
        while(strcmp(question,fgets(reponse,TAILLE_MAX_DIAL,fDial))!=0)
        {}

        for(i=0;i<=(rand()%3);i++)  {fgets(reponse,TAILLE_MAX_DIAL,fDial);}

        fclose(fDial);
    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Dialogues.txt");
    }
}



char obtenirInfo(Dialogue* dialogue, char* info)
{
    int test;
    char nomPNJ[30];

    getPersoNom(nomPNJ, dialogue->perso2);

    test=(rand()%100);

    if(test<(dialogue->humeur))
    {
        strcat(nomPNJ,"\n");
        setReponse(nomPNJ, info);
    }
    else
    {
        setReponse("Refus info\n", info);
    }

    printf("\n%s",info);
    setDialogueHumeur(dialogue,dialogue->humeur-5);

    return dialogue->humeur;
}


char soudoyer(Dialogue* dialogue, int argent, char* rep)
{
    int test;

    setPersoArgent(dialogue->perso1, getPersoArgent(dialogue->perso1)-argent);
    setPersoArgent(dialogue->perso2, getPersoArgent(dialogue->perso2)+argent);

    if(getPersoFaction(dialogue->perso1)==3)  /*C'est plus facile de soudoyer un marchand...*/
    {
        test=(rand()%((int)(argent/2)))-5;
    }
    else
    {
        test=(rand()%((int)(argent/10)))-5;
    }
    if (test>0)
    {
        setReponse("Soudoyer réussi\n",rep);
    }
    else
    {
        setReponse("Soudoyer échoué\n",rep);
    }

    setDialogueHumeur(dialogue, dialogue->humeur+test);
    printf("\n%s", rep);
    return dialogue->humeur;
}


char menacer(Dialogue* dialogue, char* rep)
{
    int test;

    test=rand()%(getPersoAttaque(dialogue->perso1)+getPersoCharisme(dialogue->perso1))-rand()%(getPersoDefense(dialogue->perso2)+getPersoIntelligence(dialogue->perso2))+(dialogue->humeur);

    if(test>0)
    {
        setReponse("Menacer réussi\n", rep);
    }
    else
    {
        setReponse("Menacer échoué\n", rep);
    }

    printf("\n%s", rep);
    setDialogueHumeur(dialogue,dialogue->humeur+test);

    return dialogue->humeur;
}




char seduire(Dialogue* dialogue, char* rep)
{
    int test;

    if (getPersoSexe(dialogue->perso1)!=getPersoSexe(dialogue->perso1))     /*Mieux vaut séduire des individus du sexe opposé...*/
    {
        test=(rand()%getPersoCharisme(dialogue->perso1))+(dialogue->humeur)-50;
    }
    else
    {
        test=(rand()%getPersoCharisme(dialogue->perso1))-(rand()%getPersoIntelligence(dialogue->perso2))+(dialogue->humeur);
    }

    if(test>0)
    {
        setReponse("Séduire réussi\n", rep);
    }
    else
    {
        setReponse("Séduire échoué\n", rep);
    }

    printf("\n%s", rep);
    setDialogueHumeur(dialogue,dialogue->humeur+test);

    return dialogue->humeur;
}



char acheter(Dialogue* dialogue, Objet* objet, char* rep)
{
    if ((getPersoArgent(dialogue->perso1))>=(getObjetValeur(objet)))
        {
            soustraireInventaire(dialogue->perso2,objet);
            ajouterInventaire(dialogue->perso1,objet);

            setPersoArgent(dialogue->perso2,getPersoArgent(dialogue->perso2)-getObjetValeur(objet));
            setPersoArgent(dialogue->perso1,getPersoArgent(dialogue->perso1)+getObjetValeur(objet));

            strcpy(rep,"Vendu !");
        }

    else
        {
            strcpy(rep,"Je suis au regret de vous annoncer que vous n'avez pas les moyens d'effectuer cette transaction...");
        }

    printf("%s",rep);
    return(dialogue->humeur);
}




char vendre(Dialogue* dialogue, Objet* objet, char* rep)
{
    if ((getPersoArgent(dialogue->perso2))>=(getObjetValeur(objet)))
        {
            soustraireInventaire(dialogue->perso1,objet);
            ajouterInventaire(dialogue->perso2,objet);

            setPersoArgent(dialogue->perso1,getPersoArgent(dialogue->perso1)-getObjetValeur(objet));
            setPersoArgent(dialogue->perso2,getPersoArgent(dialogue->perso2)+getObjetValeur(objet));

            strcpy(rep,"Merci ! Je suis très content de cette aquisition !");
        }

    else
        {
            strcpy(rep,"Hélas, je n'ai pas les moyens pour une telle transaction...");
        }

    printf("%s",rep);
    return(dialogue->humeur);
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
    setPersoArgent(&perso,1000);
    dialogueInit(&dial,&perso,&pnj);

    for(k=0;k<20;k++)
    {
        printf("\n\n");
        obtenirInfo(&dial, information);
        soudoyer(&dial, 100, information);
        seduire(&dial, information);
        menacer(&dial, information);
    }

    return 0;
}

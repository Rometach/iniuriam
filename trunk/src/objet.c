#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/


#define TAILLE_MAX 500

void objInit (Objet *obj, char type)
{
    int i,j;
    FILE* fObjet= fopen("data/Objets.txt", "r");
    assert ((type>0)&&(type<30));
    char ligne[TAILLE_MAX];
    char tampon [2];

    if (fObjet!=NULL)
    {
        for(i=0;i<type+3;i++)
        {
            fgets(ligne,TAILLE_MAX,fObjet);
        }
        i= strchr (ligne, '/')-ligne;

        strncpy(obj->nom,ligne,i);
        obj->nom[i]='\0';

        obj->type = type;

        strncpy(tampon,ligne+i+2,2);
        obj->portee=(char)atoi(tampon);

        strncpy(tampon,ligne+i+6,2);
        obj->degats=(char)atoi(tampon);

        strncpy(tampon,ligne+i+9,2);
        obj->protection=(char)atoi(tampon);
        i+=12;

        j=strchr(ligne+i,'/')-(ligne+i);
        strncpy(obj->description,ligne+i,j);
        obj->description[j]='\0';

        obj->valeur=atoi(ligne+i+j+2);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Objets.txt\n");
    }
    fclose (fObjet);
}



char getObjetType(Objet *obj)
{
	return obj->type;
}


char getObjetPortee(Objet *obj)
{
	return obj->portee;
}


char getObjetDegats(Objet *obj)
{
	return obj->degats;
}


char getObjetProtection(Objet *obj)
{
	return obj->protection;
}


int getObjetValeur(Objet *obj)
{
	return obj->valeur;
}


char* getObjetNom(Objet *obj)
{
	return obj->nom;
}


void getObjetDescription(char* s, Objet *obj)
{
	strcpy(s,obj->description);
}


int mainObjet ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}

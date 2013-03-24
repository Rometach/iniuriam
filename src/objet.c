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
    int i=0,j;
    FILE* fObjet= fopen("../data/Objets.txt", "r");
    assert ((type>0)&&(type<30));
    char *ligne = (char*) malloc (TAILLE_MAX*sizeof(char));

    if (fObjet!=NULL)
    {
        while (i<type+3)
        {
            fgets(ligne,TAILLE_MAX,fObjet);
            i++;
        }
        i= strchr (ligne, '/')-ligne;
        strncpy(obj->nom,ligne,i);
        obj->nom[i]='\0';
        obj->type = type;
        obj->portee=ligne[i+2];
        obj->degats=ligne[i+4];
        obj->protection=ligne[i+6];
        i+=8;
        j=strchr(ligne+i,'/')-(ligne+i);
        strncpy(obj->description,ligne+i,j);
        obj->description[j]='\0';
        obj->valeur=atoi(ligne+i+j+2);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Objets.txt");
    }
    fclose (fObjet);
    free (ligne);
}

void stockInit (Stock *obj)
{
    obj->objet= (Objet*) malloc (sizeof (Objet));
    obj->quantite=0;
}

void stockLibere (Stock *obj)
{
    free (obj->objet);
    obj->quantite=0;
}

int mainobjet ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}

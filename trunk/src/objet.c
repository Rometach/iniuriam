#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, Isabelle
*/

void objInit (Objet *obj, char nom[], char type, char portee, char degats, char protection, char description [], int valeur)
{
    int i;

    assert ((strlen (nom)<30)&&(strlen (description)<100));
    for (i=0;i<strlen (nom);i++)
        obj->nom [i]= nom [i];
    obj->type = type;
    obj->portee = portee;
    obj->degats = degats;
    obj->protection = protection;
    for (i=0; i<strlen (description); i++)
    {
        obj->description [i]=description[i];
    }
    obj->valeur=valeur;
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

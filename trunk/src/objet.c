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
    char tampon [2];

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
        printf ("%s\n",obj->nom);
        obj->type = type;
        printf ("%d\n", type);

        strncpy(tampon,ligne+i+2,2);
        obj->portee=(char)atoi(tampon);
        printf("%d\n",obj->portee);
        strncpy(tampon,ligne+i+6,2);
        obj->degats=(char)atoi(tampon);
        printf("%d\n",obj->degats);
        strncpy(tampon,ligne+i+9,2);
        obj->protection=(char)atoi(tampon);
        printf ("%d\n",obj->protection);
        i+=12;
        j=strchr(ligne+i,'/')-(ligne+i);
        strncpy(obj->description,ligne+i,j);
        obj->description[j]='\0';
        printf ("%s\n", obj->description);
        obj->valeur=atoi(ligne+i+j+2);
        printf ("%d\n",obj->valeur);
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

int main ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}

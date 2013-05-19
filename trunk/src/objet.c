#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void objInit (Objet *obj, char type)
{
    int i,j;
    FILE* fObjet= fopen("data/Objets.txt", "r");
    assert (type>0);
    char ligne[TAILLE_MAX_FICHIER];
    char tampon [2];

    if (fObjet!=NULL)
    {
        for(i=0;i<type+3;i++)
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fObjet);
        }
        /*Passe les premières ligne du fichier Objets.txt*/

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

        obj->utilite=(char)atoi(&ligne[i+9]);
        i+=13;

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

char getObjetUtilite(Objet *obj)
{
	return obj->utilite;
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


char* getObjetDescription(Objet *obj)
{
	return obj->description;
}

int getNbObjet()
{
    int max=0;
    FILE* fobj;
    char ligne[TAILLE_MAX_FICHIER];
    assert(fobj=fopen("data/Objets.txt","r"));
    if (fobj!=NULL)
    {
        do
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fobj);
            max++;
        }while (ligne[0]!='/'&&ligne[1]!='/');
    }
    fclose(fobj);
    return max;
}

void initialiserTousLesObjets(Objet* tabObj)
{
    int i;
    int max = getNbObjet();

//    tabObj=(Objet*)malloc(max*sizeof(Objet));
        for(i=1;i<max-4;i++)
        {
            objInit(&tabObj[i],i);
        }
}


void libererTousLesObjets(Objet* tabObj)
{
    free(tabObj);
}




int mainObjet ()
{
    Objet obj;
    objInit(&obj, 1);
    printf ("No problem \n");
    return 0;
}

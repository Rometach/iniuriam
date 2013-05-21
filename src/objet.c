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
    assert ((type>0)&&(type<=getNbObjet()-3));
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

        strncpy(tampon,ligne+i+11,1);
        obj->utilite=(char)atoi(tampon);
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

char* getObjetUtiliteNom (Objet *obj)
{
    switch (obj->utilite)
    {
        case 1 :
            return "Arme";
        break;
        case 2 :
            return "Armure";
        break;
        case 3 :
            return "Potion ou nourriture";
        break;
        case 4 :
            return "Objet de quete";
        break;
        case 5 :
            return "Autre";
        break;
        default :
            return "Indefini";
        break;
    }
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

void setObjetNom(Objet* obj,char* nom)
{
    assert (strlen(nom)<30);
    strcpy (obj->nom,nom);
}

void setObjetPortee(Objet* obj,int portee)
{
    obj->portee=portee;
}

void setObjetDegats(Objet* obj,int degats)
{
    obj->degats=degats;
}

void setObjetProtection(Objet* obj,int protection)
{
    obj->protection=protection;
}

void setObjetUtilite(Objet* obj,int utilite)
{
    if(utilite<=0||utilite>5) obj->utilite=6;
    else obj->utilite=utilite;
}

void setObjetValeur(Objet* obj,int valeur)
{
    obj->valeur=valeur;
}

void setObjetDescription(Objet* obj,char* description)
{
    assert (strlen(description)<100);
    strcpy(obj->description,description);
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

void initialiserTousLesObjets(Objet** tabObj)
{
    int i;
    int max = getNbObjet();

    (*tabObj)=(Objet*)malloc(max*sizeof(Objet));


    for(i=1;i<max-3;i++)
        {
            objInit(&((*tabObj)[i]),i);
        }
}


void libererTousLesObjets(Objet** tabObj)
{
    free(*tabObj);
}

void copierFichier (char* fichier1, char* fichier2)
{
    FILE* fSource= fopen(fichier1, "r");
    FILE* fDest= fopen(fichier2, "w+");
    char ligne [TAILLE_MAX_FICHIER];

    assert (fSource!=NULL&&fDest!=NULL);
    while (fgets(ligne,TAILLE_MAX_FICHIER,fSource)!=NULL)
    {
        fprintf(fDest,"%s",ligne);
    }
    fclose (fSource);
    fclose (fDest);
}


void afficherObjet(Objet* obj)
{
    printf("\nObjet %s :\nType %d\nUtilite %d\nPortee %d\nDegats %d\nProtection %d\nValeur %d\n%s\n\n", obj->nom, obj->type, obj->utilite, obj->portee, obj->degats, obj->protection, obj->valeur, obj->description);
}



int mainObjet()
{
    int i;
    Objet* tabObj;

    initialiserTousLesObjets(&tabObj);

    for(i=0;i<getNbObjet()-3;i++)
    {
        printf("%d%d\n",i,i);
        afficherObjet(&(tabObj[i]));
    }
    printf("BLABLA\n");
    libererTousLesObjets(&tabObj);
    return 0;
}

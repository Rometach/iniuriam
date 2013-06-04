#include "objet.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void objInit (Objet *obj, const char type)
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

        strncpy(tampon,ligne+i+5,2);
        obj->degats=(char)atoi(tampon);

        strncpy(tampon,ligne+i+8,2);
        obj->protection=(char)atoi(tampon);

        obj->utilite=ligne[i+11]-'0';
        i+=13;

        j=strchr(ligne+i,'/')-(ligne+i);
        strncpy(obj->description,ligne+i,j);
        obj->description[j]='\0';

        obj->valeur=atoi(ligne+i+j+2);

        switch(obj->utilite)
        {
            case 1: obj->icon=IMG_Load("data/Media/objetArme.gif");
            break;

            case 2: obj->icon=IMG_Load("data/Media/objetArmure.gif");
            break;

            case 3: obj->icon=IMG_Load("data/Media/objetSoin.gif");
            break;

            case 4: obj->icon=IMG_Load("data/Media/objetQuete.gif");
            break;

            default: obj->icon=IMG_Load("data/Media/objetAutre.gif");
            break;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Objets.txt\n");
    }
    fclose (fObjet);
}

void objLibere (Objet* obj)
{
    SDL_FreeSurface(obj->icon);
}

char getObjetType(const Objet *obj)
{
	return obj->type;
}

char getObjetUtilite(const Objet *obj)
{
	return obj->utilite;
}

void getObjetUtiliteNom (char* utilite, const Objet *obj)
{
    switch (obj->utilite)
    {
        case 1 :
            strcpy(utilite, "Arme");
        break;
        case 2 :
            strcpy(utilite, "Armure");
        break;
        case 3 :
            strcpy(utilite, "Potion ou nourriture");
        break;
        case 4 :
            strcpy(utilite, "Objet de quete");
        break;
        case 5 :
            strcpy(utilite, "Autre");
        break;
        default :
            strcpy(utilite, "Indefini");
        break;
    }
}

char getObjetPortee(const Objet *obj)
{
	return obj->portee;
}


char getObjetDegats(const Objet *obj)
{
	return obj->degats;
}


char getObjetProtection(const Objet *obj)
{
	return obj->protection;
}


int getObjetValeur(const Objet *obj)
{
	return obj->valeur;
}


void getObjetNom(char* nom, const Objet *obj)
{
	strcpy(nom, obj->nom);
}


void getObjetDescription(char* description, const Objet *obj)
{
	strcpy(description, obj->description);
}

void setObjetNom(Objet* obj, const char* nom)
{
    assert (strlen(nom)<30);
    strcpy (obj->nom,nom);
}

void setObjetPortee(Objet* obj, const int portee)
{
    obj->portee=portee;
}

void setObjetDegats(Objet* obj, const int degats)
{
    obj->degats=degats;
}

void setObjetProtection(Objet* obj, const int protection)
{
    obj->protection=protection;
}

void setObjetUtilite(Objet* obj,const int utilite)
{
    if(utilite<=0||utilite>5) obj->utilite=6;
    else obj->utilite=utilite;
}

void setObjetValeur(Objet* obj,const int valeur)
{
    obj->valeur=valeur;
}

void setObjetDescription(Objet* obj, const char* description)
{
    assert (strlen(description)<100);
    strcpy(obj->description,description);
}

void setObjetIcon(Objet* obj)
{
    if(obj->icon!=NULL)
    {
        SDL_FreeSurface(obj->icon);
    }

    switch(obj->utilite)
    {
        case 1: obj->icon=IMG_Load("data/Media/objetArme.gif");
        break;

        case 2: obj->icon=IMG_Load("data/Media/objetArmure.gif");
        break;

        case 3: obj->icon=IMG_Load("data/Media/objetSoin.gif");
        break;

        case 4: obj->icon=IMG_Load("data/Media/objetQuete.gif");
        break;

        default: obj->icon=IMG_Load("data/Media/objetAutre.gif");
        break;
    }
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
    int i,max;
    max=getNbObjet();
    for (i=1;i<max-3;i++)
    {
        objLibere(&((*tabObj)[i]));
    }
    free(*tabObj);
}


void copierFichier (char* fichier1, const char* fichier2)
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


void afficherObjet(const Objet* obj)
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "personnage.h"
#include "SDL/SDL.h"
#include "inventaire.h"
#include "capacite.h"
#include "objet.h"
#include "SDL/SDL.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500

void persoInit (Personnage* perso)
{
    strcpy(perso->nom,"");
    perso->race=0;
    perso->sexe=0;
    perso->faction=0;
    perso->carriere=0;
    perso->argent=0;
    perso->experience=0;

    perso->attaque=0;
    perso->defense=0;
    perso->intelligence=0;
    perso->agilite=0;
    perso->charisme=0;
    perso->ptDeVie=0;

    perso->posX=0;
    perso->posY=0;
}


void nouveauPerso (Personnage *perso, char nom[], char race, char sexe, char faction, char carriere, int experience,int argent, Objet* tab)
{
    int i=0, j,k;
    FILE* fCarr,*fRace;
    Competence* compTampon;
    char ligne [TAILLE_MAX],tampon[2];

    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);

    perso->race= race;
    perso->sexe= sexe;
    perso->faction= faction;
    perso->carriere=carriere;
    perso->argent=argent;
    perso->experience= experience;

    inventaireInit(&(perso->inventaire));

    assert (fRace= fopen("data/Races.txt", "r"));
    if (fRace!=NULL)
    {
        while (i<race+3)
        {
            fgets(ligne,TAILLE_MAX,fRace);
            i++;
        }
        i= (int)(strchr (ligne, '/')-ligne);
        strncpy(tampon,ligne+i+2,2);
        perso->attaque =(char)atoi(tampon);
        strncpy(tampon,ligne+i+5,2);
        perso->defense =(char)atoi(tampon);
        strncpy(tampon,ligne+i+8,2);
        perso->intelligence =(char)atoi(tampon);
        strncpy(tampon,ligne+i+11,2);
        perso->agilite =(char)atoi(tampon);
        strncpy(tampon,ligne+i+14,2);
        perso->charisme =(char)atoi(tampon);
        perso->ptDeVie= 100-(40-perso->defense)*3;

        j=(int)(strchr (ligne, '!')-ligne);
        for (k=i+17;k<j;k+=3)
        {
            strncpy(tampon,ligne+k,2);
            ajouterObjetInventaire(&(perso->inventaire), tab+((char)atoi(tampon)));
        }
        fclose(fRace);
    }

    i=0;

    CapaciteInit(&(perso->capacite));

    assert(fCarr= fopen("data/Carrieres.txt", "r"));
    if (fCarr!=NULL)
    {
        while (i<carriere+3)
        {
            fgets(ligne,TAILLE_MAX,fCarr);
            i++;
        }
        i= (int)(strchr (ligne, '/')-ligne);
        j= (int)(strchr (ligne,'!')-ligne);
        compTampon=(Competence*)malloc(((j-i-1)/2)*sizeof(Competence));
        for (k=i; k+1<j;k+=2)
        {
            compInit (compTampon+(k-i)/2,ligne[k+2]-'0', experience);
            ajouterCompetenceCapacite (&(perso->capacite), compTampon+(k-i)/2,experience);
        }
        fclose(fCarr);
        free(compTampon);
    }
    else printf ("Impossible d'ouvrir le fichier Carrieres.txt\n");

    equiInit(&perso->equipement);

    /*Initialiser SDL_Surface*/
}


void persoLibere (Personnage *perso)
{
    inventaireLibere(&perso->inventaire);
    CapaciteLibere(&perso->capacite);
}


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
        case 0 :
            strcpy(chaine,"Sistéen");
        case 1 :
            strcpy(chaine,"Heredian");
        case 2 :
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
        char ligne [TAILLE_MAX];
        for (i=0;i<carriere+3;i++)
        {
           fgets(ligne,TAILLE_MAX,fCarr);
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

void getPersoInventaire(Personnage *perso, Inventaire* inv)
{
    copieInventaire(inv,&perso->inventaire);
}

Inventaire* getPersoInventaire2(Personnage *perso)
{
    return &(perso->inventaire);
}

void getPersoCapacite(Personnage *perso, Capacite* s)
{
    int i;
    free (s->comp);
    s->nbCompetence= perso->capacite.nbCompetence;
    s->quantite= perso->capacite.quantite;
    s->comp=(Competence*)malloc (sizeof(Competence));
    for (i=0;i<s->nbCompetence;i++)
    {
        s->comp[i]=perso->capacite.comp[i];
    }
}

Capacite* getPersoCapacite2(Personnage *perso)
{
    return &perso->capacite;
}

Equipement* getPersoEquipement(Personnage *perso)
{
    return &perso->equipement;
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

void ajouterInventaire (Personnage *perso, Objet *obj)
{
    ajouterObjetInventaire(&perso->inventaire, obj);
}

void soustraireInventaire (Personnage *perso, Objet *obj)
{
    enleverObjetInventaire(&(perso->inventaire),obj);
}

void ajouterCompetencePerso (Personnage *perso, int type,int exp)
{
    assert(type>0);
    Competence* compTampon;
    compTampon=(Competence*)malloc(sizeof(Competence));
    compInit (compTampon,type, exp);
    ajouterCompetenceCapacite (&(perso->capacite), compTampon,exp);
    free(compTampon);
}

void persoUtiliseObjet (Personnage *perso,Objet *obj)
{
    /* Effet en fonction du type ; appel à soustraireInventaire si besoin ! */
}

void copiePerso (Personnage* perso1, Personnage* perso2)
{
    strcpy(perso2->nom,perso1->nom);
    perso2->race=perso1->race;
    perso2->sexe=perso1->sexe;
    perso2->faction=perso1->faction;
    perso2->carriere=perso1->carriere;
    perso2->argent=perso1->argent;
    perso2->experience=perso1->experience;

    copieCapacite(&perso1->capacite,&perso2->capacite);

    perso2->attaque=perso1->attaque;
    perso2->defense=perso1->defense;
    perso2->intelligence=perso1->intelligence;
    perso2->agilite=perso1->agilite;
    perso2->charisme=perso1->charisme;
    perso2->ptDeVie=perso1->ptDeVie;

    perso2->posX=perso1->posX;
    perso2->posY=perso1->posY;
    copieInventaire(&perso2->inventaire,&perso1->inventaire);

    /*Initialiser SDL_Surface*/
}

void equiper (Personnage* perso, Objet* obj)
{

    switch(getObjetUtilite(obj))
    {
        case 1: /*Arme*/
            setMainDroite (&perso->equipement,obj);
        break;
        case 2:/*Armure*/
            switch (getObjetPortee(obj))
            {
                case 1: /*Casque*/
                    setEquiTete(&perso->equipement, obj);
                break;
                case 2: /*Plastron*/
                    setEquiTorse(&perso->equipement, obj);
                break;
                case 3: /*Jambière*/
                    setEquiBas(&perso->equipement, obj);
                break;
                case 4: /*Gantelets*/
                    setEquiMains(&perso->equipement, obj);
                break;
                case 5: /*Sandales*/
                    setEquiPieds(&perso->equipement, obj);
                break;
                case 6: /*Bouclier (main gauche)*/
                    setMainGauche(&perso->equipement, obj);
                break;
                default: /*Souci*/
                    printf("Le type de votre objet est incoherent\n");
                break;
            }
        break;
        default: /*Autre*/
            printf("Vous ne pouvez vous équiper de cet objet.\n\n");
        break;

    }
}

int mainPerso()
{
    char tab[100];
    char tab2[100];
    Objet *liste;
    liste=(Objet*)malloc(40*sizeof(Objet));
    initialiserTousLesObjets(liste);

    Personnage perso;
    nouveauPerso (&perso, "Toromis", 1, 1, 1, 1, 0, 100,liste);
    getPersoNom(tab, &perso);
    printf("\n%s\n",tab);
    printf("\n%d\n",getPersoRace(&perso));
    printf("\n%d\n",getPersoSexe(&perso));

    printf("\n%d\n",getPersoCarriere(&perso));

    getCarriereNom(getPersoCarriere(&perso), tab2);
    printf("\n%s\n",tab2);

    printf("\n%d\n",getPersoArgent(&perso));
    printf("\n%d\n",getPersoExperience(&perso));
    printf("\n%d\n",getPersoAttaque(&perso));
    printf("\n%d\n",getPersoDefense(&perso));
    printf("\n%d\n",getPersoIntelligence(&perso));
    printf("\n%d\n",getPersoAgilite(&perso));
    printf("\n%d\n",getPersoCharisme(&perso));
    printf("\n%d\n",getPersoPtDeVie(&perso));

    persoLibere(&perso);
    free(liste);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "personnage.h"
#include "inventaire.h"
#include "capacite.h"
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500



void ajouterCompetencePersonnage (Personnage* perso, Competence* comp)
{
    ajouterCompetenceCapacite(&(perso->capacite), comp);
}

void persoInit (Personnage *perso, char nom[], char race, char sexe, char faction, char carriere, int experience,int argent)
{
    int i=0, j,k;
    FILE* fCarr,*fRace;
    Competence compTampon;
    char ligne [TAILLE_MAX],tampon[2];
    Objet* tab;
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
        perso->ptDeVie= 100-(20-perso->defense)*3;

        j=(int)(strchr (ligne, '!')-ligne);
        tab=(Objet*) malloc((j-i+17)*sizeof(Objet));
        for (k=i+17;k<j;k+=3)
        {
            strncpy(tampon,ligne+k,2);
            objInit(tab+k-i-17,(char)atoi(tampon));
            ajouterObjetInventaire(&(perso->inventaire), tab+k-i-17);
        }
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
        while (i+1<j)
        {
            i+=2;
            compInit (&compTampon,ligne[i]-'0', experience/10);
            ajouterCompetencePersonnage (perso, &compTampon);
        }
        fclose(fCarr);
    }
    else printf ("Impossible d'ouvrir le fichier Carrieres.txt\n");
}


void persoLibere (Personnage *perso)
{
    inventaireLibere(&perso->inventaire);
    perso->inventaire.nbObjet=0;
    perso->inventaire.capacite=0;
    free (perso->capacite.comp);
    perso->capacite.nbCompetence=0;
    perso->capacite.quantite=0;
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

char getPersoPtDeVie(Personnage *perso)
{
    return perso->charisme;
}

void getPersoInventaire(Personnage *perso, Inventaire* inv)
{
    copieInventaire(inv,&perso->inventaire);
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


void setPersoArgent(Personnage *perso, int somme)
{
    perso->argent=somme;
}


/**Cette fonction doit être recodée en utilisant eneleverObjetInventaire SVP*/
void soustraireInventaire (Personnage *perso, Objet *obj)
{
    int i=0;
    while ((i<perso->inventaire.nbObjet)&&(perso->inventaire.st[i].objet->nom!=obj->nom))
    {
        i++;
    }
    perso->inventaire.st[i].quantite--;
    /*effet en fonction du type ...*/
}




int mainPerso()
{
    char tab[100];
    char tab2[100];
    Personnage perso;
    persoInit (&perso, "Toromis", 1, 1, 1, 1, 0, 100);
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
    return 0;
}

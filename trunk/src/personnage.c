#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "personnage.h"
#include "inventaire.h"
#include "capacite.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500
#define TAILLE_INVENTAIRE 5




void ajouterCompetencePersonnage (Personnage* perso, Competence* comp)
{
    ajouterCompetenceCapacite(&(perso->capacite), comp);
}

void persoInit (Personnage *perso, char nom[], char race, char sexe, char carriere, int experience,int argent)
{
    int i=0, j;
    FILE* fCarr;
    Competence compTampon;
    char ligne [TAILLE_MAX];

    assert (strlen(nom)<30);
    strcpy(perso->nom,nom);
    perso->race= race;
    perso->sexe= sexe;
    perso->carriere=carriere;
    perso->argent=argent;
    perso->experience= experience;

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
    else
    {
        printf ("Impossible d'ouvrir le fichier Carrieres.txt");
    }

    inventaireInit(&(perso->inventaire),TAILLE_INVENTAIRE);
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
    int i;
    free (inv->st);
    inv->nbObjet=perso->inventaire.nbObjet;
    inv->capacite=perso->inventaire.capacite;
    inv->st=(Stock*)malloc ((inv->nbObjet) *sizeof(Stock));
    for (i=0; i<inv->nbObjet;i++)
    {
        inv->st[i]=perso->inventaire.st [i];
    }
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

void ajouterInventaire (Personnage *perso, Objet *obj)
{
    int i=0;

    while ((i<perso->inventaire.nbObjet)||(perso->inventaire.st[i].objet->nom!=obj->nom))
    {
        i++;
    }
    if (i<perso->inventaire.nbObjet)
    {
        perso->inventaire.st[i].quantite++;
    }
    else if (perso->inventaire.capacite==0);
    {
        Stock *tampon= perso->inventaire.st;

        perso->inventaire.st= (Stock*) malloc (2*(perso->inventaire.nbObjet)*sizeof(Stock));
        for (i=0; i<perso->inventaire.nbObjet; i++)
        {
            perso->inventaire.st [i]=tampon[i];
        }
        free (tampon);
        perso->inventaire.capacite=perso->inventaire.nbObjet;
    }
    perso->inventaire.capacite--;
    perso->inventaire.st[perso->inventaire.nbObjet].objet=obj;
    perso->inventaire.nbObjet++;
}

void utiliser (Personnage *perso, Objet *obj)
{
    int i;
    while ((i<perso->inventaire.nbObjet)&&(perso->inventaire.st[i].objet->nom!=obj->nom))
    {
        i++;
    }
    perso->inventaire.st[i].quantite--;
    /*effet en fonction du type ...*/
}

int main()
{
    char tab[100];
    char tab2[100];
    Personnage perso;
    persoInit (&perso, "Toromis", 1, 1, 1, 0, 100);
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

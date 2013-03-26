#ifndef __personnage_h__
#define __personnage_h__

#include <stdio.h>
#include <stdlib.h>
#include "competence.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Stock* obj;
    int nbObjet;
    int capacite;
} Inventaire;

typedef struct
{
    Competence *comp;
    int nbCompetence;
    int quantite;
} Capacite;

typedef struct
{
    char nom [30];
    char race;
    char sexe;
    char carriere;
    int argent;
    int experience;

    Capacite capacite;

    char attaque;
    char defense;
    char intelligence;
    char agilite;
    char charisme;
    char ptDeVie;

    Inventaire inventaire;
} Personnage;

void ajouterCompetence (Personnage* perso, Competence* comp);


/**
* \brief Preconditions : perso n'a pas déjà été initialisé
* <br /> Postconditions : perso est initialisé avec pour paramètres nom, race, sexe, carriere, et expérience
*/
void persoInit (Personnage *perso, char nom[], char race, char sexe, char carriere,int experience, int argent);

/**
* \brief Preconditions : inventaire est initialisé
* <br /> Postconditions : inventaire est libéré
*/
void inventaireLibere (Inventaire* inventaire);

/**
* \brief Preconditions : capacite est initialisé
* <br /> Postconditions : capacite est libéré
*/
void CapaciteLibere (Capacite* capacite);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : perso est libéré
*/
void persoLibere (Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de perso
*/
char* getPersoNom(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la race du perso
*/
char getPersoRace(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le sexe du perso
*/
char getPersoSexe(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la carriere du perso
*/
char getPersoCarriere(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de la carriere dans s
*/
void getCarriereNom(char carriere, char* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'argent du perso
*/
int getPersoArgent(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'experience du perso
*/
int getPersoExperience(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'attaque du perso
*/
char getPersoAttaque(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la defense du perso
*/
char getPersoDefense(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'intelligence du perso
*/
char getPersoIntelligence(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'agilite du perso
*/
char getPersoAgilite(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le charsime du perso
*/
char getPersoCharisme(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne les points de vie du perso
*/
char getPersoPtDeVie(Personnage *perso);

/**
* \brief Preconditions : perso et s sont initialisés
* <br /> Postconditions : retourne l'inventaire du perso dans s
*/
void getPersoInventaire(Personnage *perso, Inventaire* s);

/**
* \brief Preconditions : perso et s sont initialisés
* <br /> Postconditions : retourne l'ensemble des capacite du perso dans s
*/
void getPersoCapacite(Personnage *perso, Capacite* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : obj est ajouter à l'inventaire de perso
*/
void ajouterInventaire (Personnage *perso, Objet *obj);

/**
* \brief Preconditions : perso est initialisé, obj est dans l'inventaire de perso
* <br /> Postconditions : 1 obj est retiré de l'inventaire de perso
*/
void utiliser (Personnage *perso,Objet *obj);

#endif

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
* \brief Preconditions : operso est initialisé
* <br /> Postconditions : perso est libéré
*/
void persoLibere (Personnage *perso);

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

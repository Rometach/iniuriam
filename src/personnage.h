#ifndef __personnage_h__
#define __personnage_h__

#include <stdio.h>
#include <stdlib.h>
#include "inventaire.h"
#include "capacite.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char nom [30];
    char race;
    char sexe;
    char faction;
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

void ajouterCompetencePersonnage (Personnage* perso, Competence* comp);


/**
* \brief Preconditions : perso n'a pas déjà été initialisé
* <br /> Postconditions : perso est initialisé avec pour paramètres nom, race, sexe, carriere, et expérience
*/
void persoInit (Personnage *perso, char nom[], char race, char sexe, char faction, char carriere,int experience, int argent);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : perso est libéré
*/
void persoLibere (Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de perso
*/
void getPersoNom(char* maChaine, Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la race du perso
*/
char getPersoRace(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la faction du perso
*/
char getPersoFaction(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : copie le nom de la faction de perso dans chaine
*/
void getPersoFactionNom(char* chaine, Personnage *perso);

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
* \brief Preconditions : perso est initialisé mais pas inv
* <br /> Postconditions : retourne l'inventaire du perso dans s
*/
void getPersoInventaire(Personnage *perso, Inventaire* inv);

/**
* \brief Preconditions : perso et s sont initialisés
* <br /> Postconditions : retourne l'ensemble des capacite du perso dans s
*/
void getPersoCapacite(Personnage *perso, Capacite* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : fixe à somme l'argent de perso
*/
void setPersoArgent(Personnage *perso, int somme);

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

#ifndef __competence_h__
#define __competence_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "constante.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char action [30];   /**Description de ce à quoi sert la Compétence*/
    char type;          /**Correspond à la ligne où est décrite la Compétence dans Competence.txt*/
    int experience;     /**L'expérience associée à cette Compétence, qui augmente à chaque fois qu'on l'utilise*/
    char bonusatt;      /**Bonus d'attaque accordé par la Compétence*/
    char bonusdef;      /**Bonus de défenseaccordé par la Compétence*/
    char bonusint;      /**Bonus d'intelligence accordé par la Compétence*/
    char bonusagi;      /**Bonus d'agilité accordé par la Compétence*/
    char bonuschar;     /**Bonus de charisme accordé par la Compétence*/
}Competence;



/**
* \brief Preconditions : comp n'a pas déjà été initialisée ; 0<type<30
* <br /> Postconditions : comp est initialisée avec les paramètres de son type et son expérience : action et bonus combat
*/
void compInit (Competence *comp, const char type, const int experience);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : copie dans action l'action correspondant à la compétence comp
*/
void getAction (const Competence *comp, char* action);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le type de la compétence comp
*/
char getType(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne l'experience liée à la compétence comp
*/
int getExperience(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le bonus d'attaque de la compétence comp
*/
char getBonusatt(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le bonus de defense de la compétence comp
*/
char getBonusdef(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le bonus d'intelligence de la compétence comp
*/
char getBonusint(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le bonus d'agilité de la compétence comp
*/
char getBonusagi(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : retourne le bonus de charisme de la compétence comp
*/
char getBonuschar(const Competence *comp);

/**
* \brief Preconditions : comp est initialisée
* <br /> Postconditions : la valeur experience est ajoutee au champ experience de comp
*/
void compExp (Competence *comp, const int experience);

/**
* \brief Preconditions : comp2 est initialisée, pas comp1 (sauf si on veut écraser)
* <br /> Postconditions : comp2 est copiée dans comp1 (qui est ainsi initialisée)
*/
void copieCompetence(Competence *comp1, const Competence *comp2);

/**
* \brief Preconditions : /
* <br /> Postconditions : teste les fonctions du module Competence
*/
int mainCompetence();


#endif

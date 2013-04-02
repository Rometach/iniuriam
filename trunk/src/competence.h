#ifndef __competence_h__
#define __competence_h__

#include <stdio.h>
#include <stdlib.h>

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char action [30];
    char type;
    int experience;
    char bonusatt;
    char bonusdef;
    char bonusint;
    char bonusagi;
    char bonuschar;
}Competence;


/**
* \brief Preconditions : comp n'a pas déjà été initialisée
* <br /> Postconditions : comp est initialisée avec les paramètres de son type et son expérience : action et bonus combat
*/
void compInit (Competence *comp, char type, int experience);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne l'action correspondant à la compétence comp
*/
char *getAction (Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le type de la compétence comp
*/
char getType(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne l'experience liée à la compétence comp
*/
int getExperience(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le bonus d'attaque de la compétence comp
*/
char getBonusatt(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le bonus de defense de la compétence comp
*/
char getBonusdef(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le bonus d'intelligence de la compétence comp
*/
char getBonusint(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le bonus d'agilité de la compétence comp
*/
char getBonusagi(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : retourne le bonus de charisme de la compétence comp
*/
char getBonuschar(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : la valeur experience est ajoutee au champ experience de comp
*/
void compExp (Competence *comp, int experience);


/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le nom de la compétence en valeur de retour
*/
char *getAction (Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le nom de la compétence en valeur de retour
*/
char getType(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne l'expérience de la compétence en valeur de retour
*/
int getExperience(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le bonus d'attaque de la compétence en valeur de retour
*/
char getBonusatt(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le bonus de défense de la compétence en valeur de retour
*/
char getBonusdef(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le bonus d'intelligence de la compétence en valeur de retour
*/
char getBonusint(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le bonus d'agilité de la compétence en valeur de retour
*/
char getBonusagi(const Competence *comp);

/**
* \brief Preconditions : comp est initialisé
* <br /> Postconditions : Donne le bonus de charisme de la compétence en valeur de retour
*/
char getBonuschar(const Competence *comp);


#endif

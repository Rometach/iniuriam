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
* <br /> Postconditions : la valeur experience est ajoutee au champ experience de comp
*/
void compExp (Competence *comp, int experience);

#endif

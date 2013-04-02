#ifndef __parole_h__
#define __parole_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso1;     /*Le joueur*/
    Personnage* perso2;     /*Le PNJ*/
    char humeur;
} Dialogue;

/**
* \brief Preconditions : dialogue n'est pas initialis�
* <br /> Postconditions : dialogue est initialis� avec les personnages perso1 et perso2
*/
void dialogueInit (Dialogue* dialogue, Personnage* perso1, Personnage* perso2);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : copie dans info l'information (�ventuellement la r�ponse n�gative) retourn�e
*/
void obtenirInfo(Dialogue* dialogue, char* info);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : la somme argent est transf�r�e d'un personnage vers l'autre, avec un �ventuel effet sur l'humeur du second
*/
void soudoyer(Dialogue* dialogue, int argent);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : le premier personnage menace le second, avec un �ventuel effet sur son humeur
*/
void menacer(Dialogue* dialogue);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : le premier personnage tente de s�duire le second, avec un �ventuel effet sur son humeur
*/
void seduire(Dialogue* dialogue);

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : dialogue est initialis� avec les personnages perso1 et perso2
*/
/*void acheter(Dialogue* dialogue, Objet* objet);*/

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : dialogue est initialis� avec les personnages perso1 et perso2
*/
/*void vendre(Dialogue* dialogue);*/

/**
* \brief Preconditions : dialogue est initialis�
* <br /> Postconditions : dialogue est initialis� avec les personnages perso1 et perso2
*/
/*void marchander(Dialogue* dialogue);*/

#endif

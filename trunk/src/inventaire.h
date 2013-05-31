#ifndef __inventaire_h__
#define __inventaire_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL/SDL.h>
#include "stock.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Stock* st;      /**Tableau (dynamique) de Stocks*/
    int nbObjet;    /**Nombre de cases utilis�es du tableau*/
    int capacite;   /**Nombre de cases disponibles*/
} Inventaire;

/**
* \brief Preconditions : inventaire n'est pas initialis�
* <br /> Postconditions : inventaire est initialis�
*/
void inventaireInit (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : inventaire est lib�r�
*/
void inventaireLibere (Inventaire* inventaire);

/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : l'objet obj est ajout� dans inventaire
*/
void ajouterObjetInventaire (Inventaire* inventaire, Objet* obj);


/**
* \brief Preconditions : inventaire est initialis�, obj fait partie d'inventaire
* <br /> Postconditions : 1 occurence d'obj est �t�e d'inventaire
*/
void enleverObjetInventaire (Inventaire* inventaire, const Objet* obj);

/**
* \brief Preconditions : inventaire2 est initialis� mais pas inventaire1
* <br /> Postconditions : inventaire2 est recopi� dans inventaire1
*/
void copieInventaire (Inventaire* inventaire1, const Inventaire* inventaire2);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : affiche le contenu de l'inventaire
*/
void afficherInventaire (const Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne 0 si obj n'est pas dans inventaire, et 1 si oui
*/
char estObjDansInv (const Inventaire* inventaire, const Objet* obj);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne le l'adresse du i�me Stock d'inventaire
*/
Stock* getInventaireStock (const Inventaire* inventaire, const int i);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne le nombre d'objets d'inventaire
*/
int getInventaireNbObjets (const Inventaire* inventaire);


/**
* \brief Preconditions : inventaire est initialis�
* <br /> Postconditions : retourne la capacit� d'inventaire
*/
int getInventaireCapacite (const Inventaire* inventaire);

#endif

#ifndef __stock_h__
#define __stock_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Objet *objet;
    int quantite;

} Stock;

/**
* \brief Preconditions : st n'a pas déjà été initialisé, obj est initialisé
* <br /> Postconditions : st est initialisé avec l'objet obj
*/
void stockInit (Stock *st, Objet* obj);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : st est libéré avec une quantite nulle
*/
void stockLibere (Stock *st);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : la quantité d'objets dans st est augmentée de n
*/
void incrementerStock(Stock *st, int n);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : retourne l'adresse de l'objet enregistré dans st
*/
Objet* getStockObjet(Stock *st);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : retourne la quantite d'objet de st
*/
int getStockQuantite(Stock* stock);

/**
* \brief Preconditions : st et obj sont initialisés
* <br /> Postconditions : initialise l'objet de st
*/
void setStockObjet (Stock *st, Objet* obj);

/**
* \brief Preconditions : st2 est initialisé, pas st1
* <br /> Postconditions : copie st2 dans st1
*/
void copieStock (Stock *st1, Stock *st2);

#endif

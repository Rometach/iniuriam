#ifndef __stock_h__
#define __stock_h__

#include <stdio.h>
#include <stdlib.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    int quantite;
    Objet *objet;
} Stock;

/**
* \brief Preconditions : st n'a pas déjà été initialisé
* <br /> Postconditions : st est initialisé avec une quantite nulle
*/
void stockInit (Stock *st);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : la quantité d'objets dans st est augmentée de n
*/
void incrementerStock(Stock *st, int n);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : la quantité d'objets dans st est diminuée de n
*/
void decrementerStock(Stock *st, int n);

/**
* \brief Preconditions : st est initialisé
* <br /> Postconditions : retourne l'adresse de l'objet enregistré dans st
*/
Objet* getStockObjet(Stock *st);

/**
* \brief Preconditions : stock1 et stock2 sont initialisés et font référence au même objet
* <br /> Postconditions : les deux Stocks sont fusionnés dans stock1 ; stock2 est libéré
*/
void fusionStocks(Stock* stock1, Stock* stock2);


#endif

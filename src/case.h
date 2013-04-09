#ifndef __case_h__
#define __case_h__

#include <stdio.h>
#include <stdlib.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{	
	char type;
	char praticable;
	char personnage;
	char piege;
	Objet* objet;
} Case;

/**
* \brief Preconditions : C n'a pas déjà été initialisé, typeCase est un type valable
* <br /> Postconditions : C est initialisé en fonction du type donné
*/
void initCase(char typeCase , Case* C);

void setPraticable(char NPraticable, Case *C);

void setPersonnage(char NPersonnage, Case* C);

void setPiege(char Piege, Case* C);

void setObjet(Case* C);

char assetPraticable(Case* C);

char assetPersonnage(Case* C);

char assetPiege(Case* C);

Objet* assetObjet(Case* C);

#endif

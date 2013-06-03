#ifndef __listePersonnage_h__
#define __listePersonnage_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "inventaire.h"
#include "capacite.h"
#include "constante.h"
#include "equipement.h"
#include "personnage.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Personnage* perso;
    int nbrPerso;
}Liste_Perso;

void listePersoInit(Liste_Perso* liste, int nbr);

void tabListePerso(Liste_Perso* liste, int nbr);

void tabListePersoInitPNJ(Liste_Perso* liste, Objet* tabObjets);

void setListePerso(Liste_Perso* liste, Personnage* perso);

int getNbrPerso(Liste_Perso* liste);

void setNbrPerso(Liste_Perso* liste, int i);

void listePersoLibere(Liste_Perso* liste);

void tabListePersoLibere(Liste_Perso* liste);

#endif

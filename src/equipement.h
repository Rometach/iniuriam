#ifndef __equipement_h__
#define __equipement_h__

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Objet* tete;
    Objet* torse;
    Objet* bas;
    Objet* mains;
    Objet* pieds;
    Objet* armeGauche;
    Objet* armeDroite;

} Equipement;

void equiInit(Equipement* equi);

void setEquiTete(Equipement* equi, Objet* tete);

void setEquiTorse(Equipement* equi, Objet* torse);

void setEquiBas(Equipement* equi, Objet* bas);

void setEquiMains(Equipement* equi, Objet* mains);

void setEquiPieds(Equipement* equi, Objet* pieds);

Objet* getEquiTete(Equipement* equi);

Objet* getEquiTorse(Equipement* equi);

Objet* getEquiBas(Equipement* equi);

Objet* getEquiMains(Equipement* equi);

Objet* getEquiPieds(Equipement* equi);

void equiLibere(Equipement* equi);

#endif

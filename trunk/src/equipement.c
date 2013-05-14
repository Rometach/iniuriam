#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "objet.h"
#include "equipement.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void equiInit(Equipement* equi)
{
    equi->tete=NULL;
    equi->torse=NULL;
    equi->bas=NULL;
    equi->mains=NULL;
    equi->pieds=NULL;
    equi->armeGauche=NULL;
    equi->armeDroite=NULL;
}

void setEquiTete(Equipement* equi, Objet* tete)
{
    equi->tete=tete;
}

void setEquiTorse(Equipement* equi, Objet* torse)
{
    equi->torse=torse;
}

void setEquiBas(Equipement* equi, Objet* bas)
{
    equi->bas=bas;
}

void setEquiMains(Equipement* equi, Objet* mains)
{
    equi->mains=mains;
}

void setEquiPieds(Equipement* equi, Objet* pieds)
{
    equi->pieds=pieds;
}

void setMainGauche(Equipement* equi, Objet* bouclier)
{
    equi->armeGauche=bouclier;
}

void setMainDroite(Equipement* equi, Objet* arme)
{
    equi->armeDroite=arme;
}

Objet* getEquiTete(Equipement* equi)
{
    return equi->tete;
}

Objet* getEquiTorse(Equipement* equi)
{
    return equi->torse;
}

Objet* getEquiBas(Equipement* equi)
{
    return equi->bas;
}

Objet* getEquiMains(Equipement* equi)
{
    return equi->mains;
}

Objet* getEquiPieds(Equipement* equi)
{
    return equi->pieds;
}

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
/*    objInit(&equi->tete);
    objInit(&equi->torse);
    objInit(&equi->bas);
    objInit(&equi->mains);
    objInit(&equi->pieds);*/
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

void equiLibere(Equipement* equi)
{

}

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

/**
* \brief Preconditions : equi n'est pas initialisé
* <br /> Postconditions : equi est initialisé
*/
void equiInit(Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : fixe l'objet équipé à la tête dans equi à tete
*/
void setEquiTete(Equipement* equi, Objet* tete);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : fixe l'objet équipé au torse dans equi à torse
*/
void setEquiTorse(Equipement* equi, Objet* torse);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : fixe l'objet équipé aux jambes dans equi à bas
*/
void setEquiBas(Equipement* equi, Objet* bas);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : fixe l'objet équipé aux mains dans equi à mains
*/
void setEquiMains(Equipement* equi, Objet* mains);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : fixe l'objet équipé aux pieds dans equi à pieds
*/
void setEquiPieds(Equipement* equi, Objet* pieds);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé à la tête dans equi
*/
Objet* getEquiTete(Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé au torse dans equi
*/
Objet* getEquiTorse(Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux jambes dans equi
*/
Objet* getEquiBas(Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux mains dans equi
*/
Objet* getEquiMains(Equipement* equi);


/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux pieds dans equi
*/
Objet* getEquiPieds(Equipement* equi);


#endif

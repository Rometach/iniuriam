#ifndef __equipement_h__
#define __equipement_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "objet.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    Objet* tete;            /**Adresse de l'armure équipée à la tête*/
    Objet* torse;           /**Adresse de l'armure équipée au torse*/
    Objet* bas;             /**Adresse de l'armure équipée aux jambes*/
    Objet* mains;           /**Adresse de l'armure équipée aux mains*/
    Objet* pieds;           /**Adresse de l'armure équipée aux pieds*/
    Objet* armeGauche;      /**Adresse de l'arme équipée à la main gauche*/
    Objet* armeDroite [3];  /**Tableau de 3 adresses d'armes équipées à la main droite*/

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
* <br /> Postconditions : fixe l'objet équipé à la main gauche dans equi à bouclier
*/
void setMainGauche(Equipement* equi, Objet* bouclier);

/**
* \brief Preconditions : equi est initialisé, 0<=i<3
* <br /> Postconditions : fixe le ième objet équipé à la main droite dans equi à arme
*/
void setMainDroite(Equipement* equi, Objet* arme, const int i);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé à la tête dans equi
*/
Objet* getEquiTete(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé au torse dans equi
*/
Objet* getEquiTorse(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux jambes dans equi
*/
Objet* getEquiBas(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux mains dans equi
*/
Objet* getEquiMains(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé aux pieds dans equi
*/
Objet* getEquiPieds(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé
* <br /> Postconditions : retourne l'objet équipé à la main gauche dans equi
*/
Objet* getEquiMainGauche(const Equipement* equi);

/**
* \brief Preconditions : equi est initialisé,0<=i<3
* <br /> Postconditions : retourne le ième objet équipé à la main droite dans equi
*/
Objet* getEquiMainDroite(const Equipement* equi, const int i);

/**
* \brief Preconditions : equi1 est initialisé,mais pas equi2
* <br /> Postconditions : copie equi1 dans equi2
*/
void copieEquipement (Equipement* equi1, Equipement* equi2);

#endif

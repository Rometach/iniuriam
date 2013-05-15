#ifndef __mission_h__
#define __mission_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"

typedef struct
{
    char accomplie;

    char type;

    char batimentCible; /*Ptet ben qu'une Case* fera l'affaire*/
    char vaisseauCible;
    Personnage* persoCible;
    Objet* objCible;
    char suite;
}Mission;


/**
* \brief Preconditions : mission n'a pas déjà été initialisée
* <br /> Postconditions : mission est initialisée
*/
void missionInit (Mission* mission);


/**
* \brief Preconditions : mission est initialisée
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien définis
*/
void missionDefinir (Mission* mission);


/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : mission est considérée comme accomplie
*/
void missionAccomplir (Mission* mission);


/**
* \brief Preconditions : tabMission est un tableau de missions initialisées et définies, de longueur l
* <br /> Postconditions : retourne 1 si les missions du tableaux forment un ensemble harmonieux, 0 sinon
*/
char sontHarmonieusesMissions (Mission* tabMission, int l);


/**
* \brief Preconditions : tabMission est un tableau de missions initialisées, de longueur l
* <br /> Postconditions : toutes les missions de tabMission sont définies et forment un ensemble harmonieux
*/
void MissionsDefinirHarmonieuses (Mission* tabMission, int l);



#endif

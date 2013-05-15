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
* \brief Preconditions : mission n'a pas d�j� �t� initialis�e
* <br /> Postconditions : mission est initialis�e
*/
void missionInit (Mission* mission);


/**
* \brief Preconditions : mission est initialis�e
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien d�finis
*/
void missionDefinir (Mission* mission);


/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : mission est consid�r�e comme accomplie
*/
void missionAccomplir (Mission* mission);


/**
* \brief Preconditions : tabMission est un tableau de missions initialis�es et d�finies, de longueur l
* <br /> Postconditions : retourne 1 si les missions du tableaux forment un ensemble harmonieux, 0 sinon
*/
char sontHarmonieusesMissions (Mission* tabMission, int l);


/**
* \brief Preconditions : tabMission est un tableau de missions initialis�es, de longueur l
* <br /> Postconditions : toutes les missions de tabMission sont d�finies et forment un ensemble harmonieux
*/
void MissionsDefinirHarmonieuses (Mission* tabMission, int l);



#endif

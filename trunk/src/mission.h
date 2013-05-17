#ifndef __mission_h__
#define __mission_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "tile.h"

typedef struct
{
    char nom[50];

    char type;  /*1 : Parler à un personnage
                  2 :
                  3 :
                  4 :
                  5 :
                  6 :*/

    int posXCible;
    int posYCible;
    char nomPerso[30];
    Objet* objCible;

    char suite;     /*0 si la mission est la dernière d'une quête
                    correspond sinon au numéro de ligne de la mission suivante dans Missions.txt*/
}Mission;


/**
* \brief Preconditions : mission n'a pas déjà été initialisée
* <br /> Postconditions : mission est initialisée
*/
void missionInit (Mission* mission);


/**
* \brief Preconditions : mission est initialisée et non définie
                         l correspond à la ligne où
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien définis
*/
void missionDefinir (Mission* mission, int l, Objet* tabObjets);


/**
* \brief Preconditions : mission est initialisée et non définie
* <br /> Postconditions : mission est définie avec des objectifs aléatoires
*/
void missionDefinirAleatoire (Mission* mission);


/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : mission est considérée comme accomplie
*/
void missionAccomplir (Mission* mission, Objet* tabObjets);


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


/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne le type de mission
*/
char getMissionType(Mission* mission);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne l'adresse de l'objet éventuellement ciblé par la mission
*/
Objet* getMissionObjet(Mission* mission);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si perso est ciblé par la mission, 1 sinon
*/
char estPersoMission(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si le lieu de coordoonnées posX et posY est ciblée par la mission
*/
char estLieuMission(Mission* mission, int posX, int posY);

#endif

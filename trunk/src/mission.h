#ifndef __mission_h__
#define __mission_h__

#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "tile.h"

typedef struct
{
    char nom[50];

    char type;  /*1 : Parler � un personnage
                  2 :
                  3 :
                  4 :
                  5 :
                  6 :*/

    int posXCible;
    int posYCible;
    char nomPerso[30];
    Objet* objCible;

    char suite;     /*0 si la mission est la derni�re d'une qu�te
                    correspond sinon au num�ro de ligne de la mission suivante dans Missions.txt*/
}Mission;


/**
* \brief Preconditions : mission n'a pas d�j� �t� initialis�e
* <br /> Postconditions : mission est initialis�e
*/
void missionInit (Mission* mission);


/**
* \brief Preconditions : mission est initialis�e et non d�finie
                         l correspond � la ligne o�
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien d�finis
*/
void missionDefinir (Mission* mission, int l, Objet* tabObjets);


/**
* \brief Preconditions : mission est initialis�e et non d�finie
* <br /> Postconditions : mission est d�finie avec des objectifs al�atoires
*/
void missionDefinirAleatoire (Mission* mission);


/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : mission est consid�r�e comme accomplie
*/
void missionAccomplir (Mission* mission, Objet* tabObjets);


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


/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne le type de mission
*/
char getMissionType(Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne l'adresse de l'objet �ventuellement cibl� par la mission
*/
Objet* getMissionObjet(Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si perso est cibl� par la mission, 1 sinon
*/
char estPersoMission(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si le lieu de coordoonn�es posX et posY est cibl�e par la mission
*/
char estLieuMission(Mission* mission, int posX, int posY);

#endif

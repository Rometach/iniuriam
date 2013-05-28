#ifndef __mission_h__
#define __mission_h__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "constante.h"


typedef struct
{
    char nom[50];

    char type;  /*1 : Parler à un personnage
                  2 : Faire parler (obtenir des infos d') un personnage
                  3 : Tuer un personnage
                  4 : Obtenir un objet
                  5 : Se rendre à un certain endroit
                  6 :*/

    int posXCible;
    int posYCible;
    char nomPerso[30];
    Objet* objCible;

    int suite;     /*0 si la mission est la dernière d'une quête
                    correspond sinon au numéro de ligne de la mission suivante dans Missions.txt*/
}Mission;


/**
* \brief Preconditions : mission n'a pas déjà été initialisée
* <br /> Postconditions : mission est initialisée
*/
void missionInit (Mission* mission);


/**
* \brief Preconditions : mission est initialisée et non définie
                         l correspond à la ligne où est écrite la mission dans le fichier Missions.txt
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien définis
*/
void missionDefinir (Mission* mission, int l, Objet* tabObjets);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : mission est considérée comme accomplie
*/
void missionAccomplir (Mission* mission, Objet* tabObjets);


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
* <br /> Postconditions : retourne 1 si perso est concerné par la mission, 0 sinon
*/
char estPersoMission(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si le lieu de coordoonnées posX et posY est ciblé par la mission, 0 sinon
*/
char estLieuMission(Mission* mission, int posX, int posY);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si l'objet obj est concerné par la mission, 0 sinon
*/
char estObjetMission(Mission* mission, Objet* obj);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si la mission est de parler à perso, 0 sinon
*/
char testMissionParlerA(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si la mission est de faire parler perso, 0 sinon
*/
char testMissionFaireParler(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si la mission est de tuer perso, 0 sinon
*/
char testMissionTuer(Mission* mission, Personnage* perso);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si la mission est d'obtenir l'objet obj, 0 sinon
*/
char testMissionObtenir(Mission* mission, Objet* obj);

/**
* \brief Preconditions : mission est initialisée et définie
* <br /> Postconditions : retourne 1 si la mission est d'aller au lieu de coordonnées (posX,posY), 0 sinon
*/
char testMissionAllerA(Mission* mission, int posX, int posY);


/**
* \brief Preconditions : /
* <br /> Postconditions : teste le module Mission
*/
int mainMission();



#endif

#ifndef __mission_h__
#define __mission_h__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "personnage.h"
#include "constante.h"


typedef struct
{
    char nom[50];       /**Intitul� de la mission*/

    char type;          /**1 : Parler � un personnage
                          2 : Faire parler (obtenir des infos d') un personnage
                          3 : Tuer un personnage
                          4 : Obtenir un objet
                          5 : Se rendre � un certain endroit
                          6 :*/

    int posXCible;      /**Si on doit se rendre � un lieu, sa coordonn�e en X*/
    int posYCible;      /**Si on doit se rendre � un lieu, sa coordonn�e en Y*/
    char nomPerso[30];  /**Si la mission concerne un PNJ, son nom*/
    Objet* objCible;    /**Si la mission concerne un objet, son adresse*/

    int suite;     /**0 si la mission est la derni�re d'une qu�te
                    correspond sinon au num�ro de ligne de la mission suivante dans Missions.txt**/
}Mission;


/**
* \brief Preconditions : mission n'a pas d�j� �t� initialis�e
* <br /> Postconditions : mission est initialis�e
*/
void missionInit (Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et non d�finie
                         l correspond � la ligne o� est �crite la mission dans le fichier Missions.txt
* <br /> Postconditions : mission est une vraie mission avec des objectifs bien d�finis
*/
void missionDefinir (Mission* mission, const int l, Objet* tabObjets);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : mission est consid�r�e comme accomplie
*/
void missionAccomplir (Mission* mission, Objet* tabObjets);

/**
* \brief Preconditions : mission1 est initialis�e et d�finie, pas mission2
* <br /> Postconditions : le contenu de mission1 est copi� dans mission2
*/
void missionCopie (Mission* mission1,const Mission* mission2);

/**
* \brief Preconditions : mission est initialis�e et d�finie ; nom est une chaine de longueur >=50
* <br /> Postconditions : copie dans nom l'intitul� de mission
*/
void getMissionNom(char* nom, const Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie ; nom est une chaine de longueur >=30
* <br /> Postconditions : copie dans nom le nom du personnage �ventuellement cibl� par mission
*/
void getMissionNomPerso(char* nomPerso, const Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne le type de mission
*/
char getMissionType(const Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne l'adresse de l'objet �ventuellement cibl� par la mission
*/
Objet* getMissionObjet(const Mission* mission);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si perso est concern� par la mission, 0 sinon
*/
char estPersoMission(const Mission* mission, const Personnage* perso);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si le lieu de coordoonn�es posX et posY est cibl� par la mission, 0 sinon
*/
char estLieuMission(const Mission* mission, const int posX, const int posY);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si l'objet obj est concern� par la mission, 0 sinon
*/
char estObjetMission(const Mission* mission, const Objet* obj);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si la mission est de parler � perso, 0 sinon
*/
char testMissionParlerA(const Mission* mission, const Personnage* perso);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si la mission est de faire parler perso, 0 sinon
*/
char testMissionFaireParler(const Mission* mission, const Personnage* perso);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si la mission est de tuer perso, 0 sinon
*/
char testMissionTuer(const Mission* mission, const Personnage* perso);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si la mission est d'obtenir l'objet obj, 0 sinon
*/
char testMissionObtenir(const Mission* mission, const Objet* obj);

/**
* \brief Preconditions : mission est initialis�e et d�finie
* <br /> Postconditions : retourne 1 si la mission est d'aller au lieu de coordonn�es (posX,posY), 0 sinon
*/
char testMissionAllerA(const Mission* mission, const int posX, const int posY);


/**
* \brief Preconditions : /
* <br /> Postconditions : teste le module Mission
*/
int mainMission();



#endif

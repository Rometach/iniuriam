#ifndef __personnage_h__
#define __personnage_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "inventaire.h"
#include "capacite.h"
#include "constante.h"
#include "equipement.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

typedef struct
{
    char nom [30];
    char race;/*0 : inconnu
                1 : humain
                2 : cyborg
                3 : sicaris
                4 : medarsins
                */
    char sexe;/*0 : inconnu
                1 : homme
                2 : femme*/
    char faction;/*0 : inconnu
                1 : Sistéen
                2 : Heredian
                3 : Marchand
                */
    char carriere;
    int argent;
    int experience;
    int niveau;

    Capacite capacite;

    char attaque;
    char defense;
    char intelligence;
    char agilite;
    char charisme;
    int ptDeVie;

    int posX;
    int posY;

    Inventaire inventaire;

    Equipement equipement;

	SDL_Surface* avatar;

} Personnage;


/**
* \brief Preconditions : perso n'a pas déjà été initialisé
* <br /> Postconditions : perso est initialisé, vide
*/
void persoInit (Personnage* perso);

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide
                        tab contient tous les objets du jeu
                        les autres paramètres respectent les critères imposés par la structure
* <br /> Postconditions : perso est initialisé et ses paramètres nom, race, sexe, carriere, et expérience sont fournis
*/
void nouveauPerso(Personnage *perso, char nom[], char race, char sexe, char faction, char carriere, int experience, int argent, Objet* tab);

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide
                         tous les paramètres respectent les critères imposés par la structure
* <br /> Postconditions : perso est initialisé avec tous les paramètres de sa structure.
*/
void chargerPerso (Personnage* perso,char nom[50],char race,char sexe,char faction,char carriere,int experience,int argent,char attaque,char defense,char intelligence,
                   char agilite,char charisme,int ptDeVie,int posX,int posY,Competence* liste,int nbCompetence,int* inventaire,int nbObjet,int armure[5],int arme[3]);

/**
* \brief Preconditions : /
* <br /> Postconditions : retourne le nombre de personnages dans PNJ.txt
*/
int getNbPNJ();

/**
* \brief Preconditions : perso n'est pas initialisé ou initialisé à vide, l<=getNbPNJ()
                        tab contient tous les objets du jeu
* <br /> Postconditions : perso est initialisé avec les paramètres du l-ième PNJ du fichier PNJ.txt
*/
void persoInitPNJ(Personnage *perso, int l, Objet* tab);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : perso est libéré
*/
void persoLibere (Personnage *perso);

/**
* \brief Preconditions : perso est initialisé, maChaine a une longueur >= 30
* <br /> Postconditions : copie le nom de perso dans maChaine
*/
void getPersoNom(char* maChaine, Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la race du perso
*/
char getPersoRace(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la faction du perso
*/
char getPersoFaction(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : copie le nom de la faction de perso dans chaine
*/
void getPersoFactionNom(char* chaine, Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le sexe du perso
*/
char getPersoSexe(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la carriere du perso
*/
char getPersoCarriere(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le nom de la carriere dans s
*/
void getCarriereNom(char carriere, char* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'argent du perso
*/
int getPersoArgent(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'experience du perso
*/
int getPersoExperience(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'attaque du perso
*/
char getPersoAttaque(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne la defense du perso
*/
char getPersoDefense(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'intelligence du perso
*/
char getPersoIntelligence(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'agilite du perso
*/
char getPersoAgilite(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne le charsime du perso
*/
char getPersoCharisme(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne les points de vie du perso
*/
int getPersoPtDeVie(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en X du perso
*/
void setPersoPosX(Personnage *perso, int x);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en X du perso
*/
int getPersoPosX(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : change la position en Y du perso
*/
void setPersoPosY(Personnage *perso, int y);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : récupère la position en Y du perso
*/
int getPersoPosY(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé mais pas inv
* <br /> Postconditions : copie l'inventaire du perso dans inv
*/
void getPersoInventaire(Personnage *perso, Inventaire* inv);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'inventaire du perso
*/
Inventaire* getPersoInventaire2(Personnage *perso);

/**
* \brief Preconditions : perso et s sont initialisés
* <br /> Postconditions : retourne l'ensemble des capacite du perso dans s
*/
void getPersoCapacite(Personnage *perso, Capacite* s);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'adresse de la Capacite de perso
*/
Capacite* getPersoCapacite2(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : retourne l'adresse de l'Equipement de perso
*/
Equipement* getPersoEquipement(Personnage *perso);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : fixe la somme d'argent du perso
*/
void setPersoArgent(Personnage *perso, int somme);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : ajoute pdv aux points de vie de perso
*/
void addPersoPtDeVie(Personnage *perso, int pdv);

/**
* \brief Preconditions : perso est initialisé
* <br /> Postconditions : 1 obj est ajouté à l'inventaire de perso
*/
void ajouterInventaire (Personnage *perso, Objet *obj);

/**
* \brief Preconditions : perso est initialisé, obj est dans l'inventaire de perso
* <br /> Postconditions : 1 obj est retiré de l'inventaire de perso
*/
void soustraireInventaire (Personnage *perso,Objet *obj);

/**
* \brief Preconditions : perso est initialisé, type >0
* <br /> Postconditions : ajoute la compétence associée à type (avec l'expérience exp) à perso
*/
void ajouterCompetencePerso (Personnage *perso, int type, int exp);

/**
* \brief Preconditions : perso est initialisé, obj est dans l'inventaire de perso
                        éventuellement, cible correspond au personnage visé, initialisé
* <br /> Postconditions : obj est utilisé et si besoin retiré de l'inventaire de perso
*/
void persoUtiliseObjet (Personnage *perso, Objet *obj, Personnage* cible);

/**
* \brief Preconditions : perso1 est initialisé, mais pas perso2
* <br /> Postconditions : le contenu de perso1 est copié dans perso2
*/
void copiePerso (Personnage* perso1, Personnage* perso2);

/**
* \brief Preconditions : perso est initialisé, obj appartient à l'inventaire de perso, 0<=i<3
* <br /> Postconditions : obj est équipé (à la ième place s'il s'agit d'une arme)
*/
void equiper (Personnage* perso,Objet* obj,int i);

/**
* \brief Preconditions : tabPNJ n'est pas initialisé
                        tabObjets contient tous les objets
* <br /> Postconditions : initialise tous les PNJ dans tabPNJ
*/
void initialiserTousLesPNJ(Personnage** tabPNJ, Objet* tabObjets);

/**
* \brief Preconditions : tabPNJ est initialisé
* <br /> Postconditions : libère tabPNJ
*/
void libererTousLesPNJ(Personnage** tabPNJ);

/**
* \brief Preconditions : experience>=0
* <br /> Postconditions : retourne le niveau lié à experience
*/
int calculNiveau(int experience);


/**
* \brief Preconditions : /
* <br /> Postconditions : Fonction de test de non-regression du module Personnage ; retourne 0 si tout s'est bien passé
*/
int mainPerso();


#endif

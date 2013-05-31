#include "mission.h"



void missionInit (Mission* mission)
{
    mission->type=0;
    strcpy(mission->nom,"");
    mission->posXCible=-1;
    mission->posXCible=-1;
    strcpy(mission->nomPerso,"");
    mission->objCible=NULL;
    mission->suite=0;
}


void missionDefinir (Mission* mission, const int l, Objet* tabObjets)
{
    int i;
    char nomPerso[30];
    int nbObj;

    char ligne [TAILLE_MAX_FICHIER];

    FILE* fMission;
    fMission=fopen("data/Missions.txt","r");

    for(i=0;i<l+3;i++)
    {
        fgets(ligne,TAILLE_MAX_FICHIER,fMission);
    }

    strcpy(mission->nom,ligne);
    strcat(mission->nom,"\0");

    fscanf(fMission,"%c %d %d %d %d %s",&mission->type, &mission->posXCible, &mission->posYCible, &nbObj, &mission->suite, nomPerso);
    mission->type=(char)atoi(&mission->type);
    if(nbObj!=0) {mission->objCible=&(tabObjets[nbObj]);}
    else {mission->objCible=NULL;}
    strcpy(mission->nomPerso,nomPerso);
}



void missionAccomplir (Mission* mission, Objet* tabObjets)
{
    if ((mission->suite)!=0)
    {
        missionDefinir(mission,mission->suite,tabObjets);
    }
    else
    {
        printf("La mission \"%s\" est finie...\n", mission->nom);
    }
}



void getMissionNom(char* nom, const Mission* mission)
{
    strcpy(nom, mission->nom);
}


void getMissionNomPerso(char* nom, const Mission* mission)
{
    strcpy(nom, mission->nomPerso);
}


char getMissionType(const Mission* mission)
{
    return mission->type;
}


Objet* getMissionObjet(const Mission* mission)
{
    return mission->objCible;
}


char estPersoMission(const Mission* mission, const Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);
    return 1-strcmp(mission->nomPerso,nom);
}


char estLieuMission(const Mission* mission, const int posX, const int posY)
{
    return (((mission->posXCible)==(posX))&&((mission->posYCible)==(posY)));
    /*Ici une proposition de code au cas où on souhaiterait simplement s'assurer que (posX,posY)
        est à distance inférieure ou égale à DIST_MAX_TEST du lieu ciblé (en norme 1) :

    int d;
    d=fabs((mission->posXCible)-(posX))+fabs((mission->posYCible)-(posY));

    return(d<=DIST_MAX_TEST);

    */
}


char estObjetMission(const Mission* mission, const Objet* obj)
{
    return (mission->objCible==obj);
}


char testMissionParlerA(const Mission* mission, const Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==1)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionFaireParler(const Mission* mission, const Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==2)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionTuer(const Mission* mission, const Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==3)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionObtenir(const Mission* mission, const Objet* obj)
{
    return ((mission->type==4)&&(mission->objCible==obj));
}


char testMissionAllerA(const Mission* mission, const int posX, const int posY)
{
    return ((mission->type==5)&&(mission->posXCible==posX)&&(mission->posYCible==posY));

    /*Ici une proposition de code au cas où on souhaiterait simplement s'assurer que (posX,posY)
        est à distance inférieure ou égale à DIST_MAX_TEST du lieu ciblé (en norme 1) :

    int d;
    d=fabs((mission->posXCible)-(posX))+fabs((mission->posYCible)-(posY));

    return ((mission->type==5)&&(d<=DIST_MAX_TEST));

    */
}





int mainMission()
{
    int i, j;
    char nom[50], nomPerso[30], nomObjet[30];
    Mission mission;
    Objet* tabObj;
    Personnage perso;

    srand(time(NULL));
    initialiserTousLesObjets(&tabObj);
    nouveauPerso (&perso, "Babar", 1, 1, 1, 1, 0, 100, tabObj);

    for(i=0;i<1;i++)
    {
        missionInit(&mission);
        missionDefinir(&mission, 1, tabObj);

        for(j=0;j<3;j++)
        {
            getMissionNom(nom, &mission);
            getMissionNomPerso(nomPerso, &mission);
            if (getMissionObjet(&mission)!=NULL) {getObjetNom(nomObjet, getMissionObjet(&mission));}
            else {strcpy(nomObjet, "Pas d'Objet !");}

            printf("Mission : %sType : %d\nPosCiblee : %d %d\nObjet : %s\nSuite : %d\nPersoCible : %s\n\n", nom, getMissionType(&mission), mission.posXCible, mission.posYCible, nomObjet, mission.suite, nomPerso);
            missionAccomplir(&mission, tabObj);
        }
    }

    return 0;
}

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


void missionDefinir (Mission* mission, int l, Objet* tabObjets)
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

    printf("\n%s\n",ligne);

    strcpy(mission->nom,ligne);
    strcat(mission->nom,"\0");
    fscanf(fMission,"%c %d %d %d %c %s",&mission->type, &mission->posXCible, &mission->posYCible, &nbObj, &mission->suite, nomPerso);
    mission->type=(char)atoi(&mission->type);
    mission->suite=(char)atoi(&mission->suite);

    printf("%d %s %d %d %d %d",mission->type, nomPerso, mission->posXCible, mission->posYCible, nbObj, mission->suite);
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



char getMissionType(Mission* mission)
{
    return mission->type;
}


Objet* getMissionObjet(Mission* mission)
{
    return mission->objCible;
}


char estPersoMission(Mission* mission, Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);
    return strcmp(mission->nomPerso,nom);
}


char estLieuMission(Mission* mission, int posX, int posY)
{
    return (((mission->posXCible)==(posX))&&((mission->posYCible)==(posY)));
    /*Ici une proposition de code au cas où on souhaiterait simplement s'assurer que (posX,posY)
        est à distance inférieure ou égale à DIST_MAX_TEST du lieu ciblé (en norme 1) :

    int d;
    d=fabs((mission->posXCible)-(posX))+fabs((mission->posYCible)-(posY));

    return(d<=DIST_MAX_TEST);

    */
}


char estObjetMission(Mission* mission, Objet* obj)
{
    return (mission->objCible==obj);
}


char testMissionParlerA(Mission* mission, Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==1)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionFaireParler(Mission* mission, Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==2)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionTuer(Mission* mission, Personnage* perso)
{
    char nom[30];
    getPersoNom(nom,perso);

    return ((mission->type==3)&&((strcmp(mission->nomPerso,nom))==0));
}


char testMissionObtenir(Mission* mission, Objet* obj)
{
    return ((mission->type==4)&&(mission->objCible==obj));
}


char testMissionAllerA(Mission* mission, int posX, int posY)
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
    srand(time(NULL));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personnage.h"
#include "mission.h"
#include "constante.h"


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


void missionDefinirAleatoire (Mission* mission)
{
    mission->type=rand()%9;
    switch(mission->type)
    {
        case 0:
        /*mission->batimentCible=*/
        break;
        case 1:
        /*mission->vaisseauCible=*/
        break;
        case 2:
        /*mission->persoCible=*/
        break;
        case 3:
        /*mission->batimentCible=*/
        break;

        case 5:
        /*mission->objetCible=*/
        break;
        case 6:
        /*mission->objetCible=*/
        break;
        case 7:
        /*mission->persoCible=*/
        break;
    }
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


char sontHarmonieusesMissions (Mission* tabMission, int l)
{
    int i,j;

    /*On vérifie qu'il n'y a pas 2 missions de même type*/
    for(i=0;i<l-1;i++)
    {
        for(j=i+1;j<l;j++)
        {
            if((tabMission[i].type)==(tabMission[j].type))
            {return 0;}
        }
    }

    /*On vérifie que le même bâtiment n'est pas en jeu plusieurs fois
    for(i=0;i<l-1;i++)
    {
        if(((tabMission[i].type)==0)||((tabMission[i].type)==3))
        {
            for(j=i+1;j<l;j++)
            {
                if(((tabMission[j].type)==0)||((tabMission[j].type)==3))
                {
                    if((tabMission[i].batimentCible)==(tabMission[j].batimentCible))
                    {return 0;}
                }
            }
        }
    }


    On vérifie que le même personnage n'est pas en jeu plusieurs fois
    for(i=0;i<l-1;i++)
    {
        if(((tabMission[i].type)==2)||((tabMission[i].type)==7))
        {
            for(j=i+1;j<l;j++)
            {
                if(((tabMission[j].type)==2)||((tabMission[j].type)==7))
                {
                    if((tabMission[i].persoCible)==(tabMission[j].persoCible))
                    {return 0;}
                }
            }
        }
    }*/         /**A CORRIGER (<=> modifications de struct Mission) !!!!! */

    /*On vérifie que le même objet n'est pas en jeu plusieurs fois*/
    for(i=0;i<l-1;i++)
    {
        if(((tabMission[i].type)==5)||((tabMission[i].type)==6))
        {
            for(j=i+1;j<l;j++)
            {
                if(((tabMission[j].type)==5)||((tabMission[j].type)==6))
                {
                    if((tabMission[i].objCible)==(tabMission[j].objCible))
                    {return 0;}
                }
            }
        }
    }

    return 1;
}


void MissionsDefinirHarmonieuses (Mission* tabMission, int l)
{
    int i;

    do
    {
        for(i=0;i<l;i++)
        {
            missionDefinirAleatoire(tabMission+i);
        }
    }
    while(!sontHarmonieusesMissions(tabMission, l));

    /*NB: Il ne s'agit pas d'une méthode excessivement rapide ;
    toutefois on n'utilisera normalement cette fonction qu'une fois dans le jeu*/
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
}





int mainMission()
{
    srand(time(NULL));

    return 0;
}

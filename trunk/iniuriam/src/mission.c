#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "personnage.h"
#include "mission.h"



void missionInit (Mission* mission)
{
    mission->accomplie=0;
    mission->type=-1;
    mission->batimentCible=0;
    mission->vaisseauCible=0;
    mission->persoCible=NULL;
    mission->objCible=NULL;
}


void missionDefinir (Mission* mission)
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


void missionAccomplir (Mission* mission)
{
    mission->accomplie=1;
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

    /*On vérifie que le même bâtiment n'est pas en jeu plusieurs fois*/
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

    /*On vérifie que le même personnage n'est pas en jeu plusieurs fois*/
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
    }

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
            missionDefinir(tabMission+i);
        }
    }
    while(!sontHarmonieusesMissions(tabMission, l));

    /*NB: Il ne s'agit pas d'une méthode excessivement rapide ;
    toutefois on n'utilisera normalement cette fonction qu'une fois dans le jeu*/
}



int mainMission()
{
    srand(time(NULL));

    return 0;
}

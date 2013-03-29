#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "competence.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500


void compInit (Competence * comp, char type, int experience)
{
    int i;
    FILE *fComp;
    assert(fComp = fopen ("data/Competences.txt", "r"));
    assert ((type>0)&&(type<30));
    char ligne[TAILLE_MAX];
    if (fComp!=NULL)
    {
        for(i=0; i<type+3; i++)
        {
            fgets(ligne,TAILLE_MAX,fComp);
        }
        i= strchr (ligne, '/')-ligne;
        strncpy(comp->action,ligne,i);
        comp->action[i]='\0';
        comp->type = type;
        comp->experience=experience;
        comp->bonusatt=(char)((experience/10)*(ligne[i+2]-'0'));
        comp->bonusdef=(char)((experience/10)*(ligne[i+4]-'0'));
        comp->bonusint=(char)((experience/10)*(ligne[i+6]-'0'));
        comp->bonusagi=(char)((experience/10)*(ligne[i+8]-'0'));
        comp->bonuschar=(char)((experience/10)*(ligne[i+10]-'0'));
        printf("OK");

    }
    else
    {
        printf ("Impossible d'ouvrir le fichier Competences.txt");
    }
  fclose (fComp);
}

char *getAction (Competence *comp)
{
    return comp->action;
}

char getType(const Competence *comp)
{
    return comp->type;
}

int getExperience(const Competence *comp)
{
    return comp->experience;
}

char getBonusatt(const Competence *comp)
{
    return comp->bonusatt;
}

char getBonusdef(const Competence *comp)
{
    return comp->bonusdef;
}

char getBonusint(const Competence *comp)
{
    return comp->bonusint;
}

char getBonusagi(const Competence *comp)
{
    return comp->bonusagi;
}

char getBonuschar(const Competence *comp)
{
    return comp->bonuschar;
}


void compExp (Competence *comp, int experience)
{
    comp->experience+=experience;
}

int mainComp()
{
    Competence comp1;
    compInit(&comp1, 1, 20);
    printf("Ok!");
    printf("%s", getAction(&comp1));
    printf("%d", getType(&comp1));
    printf("%d", getExperience(&comp1));
    printf("%d", getBonusatt(&comp1));
    printf("%d", getBonusdef(&comp1));
    printf("%d", getBonusint(&comp1));
    printf("%d", getBonusagi(&comp1));
    printf("%d", getBonuschar(&comp1));
    return 0;
}

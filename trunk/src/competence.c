#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "competence.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 500

void compInit (Competence *comp, char type, int experience)
{
    int i=0;
    FILE *fComp = fopen ("../data/Compétences.txt", "r");
    assert ((type>0)&&(type<30));
    char *ligne = (char*) malloc (TAILLE_MAX*sizeof(char));

    if (fComp!=NULL)
    {
        while (i<type+3)
        {
            fgets(ligne,TAILLE_MAX,fComp);
            i++;
        }
        i= strchr (ligne, '/')-ligne;
        strncpy(comp->action,ligne,i);
        comp->action[i]='\0';
        comp->type = type;
        comp->experience=experience;
        comp->bonusatt=(char)((experience/10)*(int)ligne[i+2]);
        comp->bonusdef=(char)((experience/10)*(int)ligne[i+4]);
        comp->bonusint=(char)((experience/10)*(int)ligne[i+6]);
        comp->bonusagi=(char)((experience/10)*(int)ligne[i+8]);
        comp->bonuschar=(char)((experience/10)*(int)ligne[i+10]);
    }
    fclose (fComp);
    free (ligne);
}

void compExp (Competence *comp, int experience)
{
    comp->experience+=experience;
}

#include "objet_Editeur.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

void objInit (Objet *obj, char type)
{
    int i,j;
    FILE* fObjet= fopen("data/Objets.txt", "r");
    assert (type>0);
    char ligne[TAILLE_MAX_FICHIER];
    char tampon [2];

    if (fObjet!=NULL)
    {
        for(i=0;i<type+3;i++)
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fObjet);
        }
        /*Passe les premières ligne du fichier Objets.txt*/

        i= strchr (ligne, '/')-ligne;
        strncpy(obj->nom,ligne,i);
        obj->nom[i]='\0';

        obj->type = type;

        strncpy(tampon,ligne+i+2,2);
        obj->portee=(char)atoi(tampon);

        strncpy(tampon,ligne+i+6,2);
        obj->degats=(char)atoi(tampon);

        strncpy(tampon,ligne+i+9,2);
        obj->protection=(char)atoi(tampon);

        strncpy(tampon,ligne+i+11,1);
        obj->utilite=(char)atoi(tampon);
        i+=13;

        j=strchr(ligne+i,'/')-(ligne+i);
        strncpy(obj->description,ligne+i,j);
        obj->description[j]='\0';

        obj->valeur=atoi(ligne+i+j+2);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Objets.txt\n");
    }
    fclose (fObjet);
}



char getObjetType(Objet *obj)
{
	return obj->type;
}

char getObjetUtilite(Objet *obj)
{
	return obj->utilite;
}

char* getObjetUtiliteNom (Objet *obj)
{
    switch (obj->utilite)
    {
        case 1 :
            return "Arme";
        break;
        case 2 :
            return "Armure";
        break;
        case 3 :
            return "Potion ou nourriture";
        break;
        case 4 :
            return "Objet de quete";
        break;
        case 5 :
            return "Autre";
        break;
        default :
            return "Indefini";
        break;
    }
}

char getObjetPortee(Objet *obj)
{
	return obj->portee;
}


char getObjetDegats(Objet *obj)
{
	return obj->degats;
}


char getObjetProtection(Objet *obj)
{
	return obj->protection;
}


int getObjetValeur(Objet *obj)
{
	return obj->valeur;
}


void getObjetNom(Objet *obj,char* nom)
{
    strcpy(nom,obj->nom);
}


char* getObjetNom2(Objet *obj)
{
    return obj->nom;
}

void getObjetDescription(Objet *obj,char* description)
{
	strcpy(description,obj->description);
}

char* getArmureType (Objet* obj)
{
    assert(obj->utilite==2);
    switch (obj->portee)
    {
        case 1 :
            return "Casque";
        break;
        case 2 :
            return "Plastron";
        break;
        case 3 :
            return "Jambieres";
        break;
        case 4 :
            return "Gants";
        break;
        case 5 :
            return "Chaussures";
        break;
        case 6:
            return "Bouclier";
        break;
        default :
            return "Indefini";
        break;
    }
}

char* getPotionType(Objet* obj)
{
    assert(obj->utilite==3);
    switch (obj->portee)
    {
        case 1 :
            return "Soin";
        break;
        case 2 :
            return "Degats";
        break;
        default :
            return "Indefini";
        break;
    }
}


void setObjetNom(Objet* obj,char* nom)
{
    assert (strlen(nom)<30);
    strcpy (obj->nom,nom);
}

void setObjetPortee(Objet* obj,int portee)
{
    obj->portee=portee;
}

void setObjetDegats(Objet* obj,int degats)
{
    obj->degats=degats;
}

void setObjetProtection(Objet* obj,int protection)
{
    obj->protection=protection;
}

void setObjetUtilite(Objet* obj,int utilite)
{
    if(utilite<=0||utilite>5) obj->utilite=6;
    else obj->utilite=utilite;
}

void setObjetValeur(Objet* obj,int valeur)
{
    obj->valeur=valeur;
}

void setObjetDescription(Objet* obj,char* description)
{
    assert (strlen(description)<100);
    strcpy(obj->description,description);
}


int getNbObjet()
{
    int max=0;
    FILE* fobj;
    char ligne[TAILLE_MAX_FICHIER];
    assert(fobj=fopen("data/Objets.txt","r"));
    if (fobj!=NULL)
    {
        do
        {
            fgets(ligne,TAILLE_MAX_FICHIER,fobj);
            max++;
        }while (ligne[0]!='/'&&ligne[1]!='/');
    }
    fclose(fobj);
    return max;
}

void initialiserTousLesObjets(Objet** tabObj)
{
    int i;
    int max = getNbObjet();
    *tabObj=(Objet*)malloc(max*sizeof(Objet));
        for(i=1;i<max-3;i++)
        {
            objInit(&((*tabObj)[i]),i);
        }
}


void libererTousLesObjets(Objet* tabObj)
{
    free(tabObj);
}

void copierFichier (char* fichier1, char* fichier2)
{
    FILE* fSource= fopen(fichier1, "r");
    FILE* fDest= fopen(fichier2, "w+");
    char ligne [TAILLE_MAX_FICHIER];

    assert (fSource!=NULL&&fDest!=NULL);
    while (fgets(ligne,TAILLE_MAX_FICHIER,fSource)!=NULL)
    {
        fprintf(fDest,"%s",ligne);
    }
    fclose (fSource);
    fclose (fDest);
}

void modifierObjet ()
{
    FILE* fObjet= fopen("data/Objets.txt", "r+");
    FILE* fTampon;
    int i,j, choix=0,max,valeur;
    int portee, degats, protection, utilite;
    char ligne [TAILLE_MAX_FICHIER],nom[50], tampon [TAILLE_MAX_FICHIER],*fin, tampon2[TAILLE_MAX_FICHIER];
    char c=1;
    Objet obj,* tab;
    assert(fObjet!=NULL);
    while (choix!=4)
    {
        printf ("Editer un objet\n\n\n1. Ajouter un objet\n\n2. Modifier un objet\n\n3. Supprimer un objet\n\n4. Quitter\n");
        scanf ("%d",&choix);
        printf ("\n\n");
        switch (choix)
        {
            case 1: /*Ajouter un objet*/
                while (choix!=0)
                {
                    max=getNbObjet();
                    initialiserTousLesObjets (&tab);
                    while (c)
                    {
                        c=0;
                        printf ("\nEntrez le nom du nouvel objet.\n");
                        scanf ("%s",nom);
                        for (i=1;i<max-4;i++)
                        {
                            if (strcmp(tab[i].nom,nom)==0)
                            {
                                c=1;
                                printf("\nEntrez un Objet qui n'appartient pas à Objets.txt\n\n");
                            }
                        }
                    }
                    c=1;
                    while (c)
                    {
                        printf("\nEntrez la portee de l'objet.\n");
                        scanf ("%d",&portee);
                        if (portee>0&&portee<100) c=0;
                        if (c) printf("\nEntrez une portee entre 1 et 100\n\n");
                    }
                    c=1;
                    while (c)
                    {
                        printf("\nEntrez les dégats de l'objet.\n");
                        scanf ("%d",&degats);
                        if (degats>0&&degats<100) c=0;
                        if (c) printf("\nEntrez des degats entre 1 et 100\n\n");
                    }
                    c=1;
                    while (c)
                    {
                        printf("\nEntrez la protection de l'objet.\n");
                        scanf ("%d",&protection);
                        if (protection>0&&protection<100) c=0;
                        if (c) printf("\nEntrez une protection entre 1 et 100\n\n");
                    }
                    c=1;
                    while (c)
                    {
                        printf("\nEntrez l'utilité de l'objet:\n1.Arme\n2.Armure\n3.Potion,Nourriture\n4.Objet de quête\n5.Autre\n\n");
                        scanf ("%d",&utilite);
                        if (utilite>0&&utilite<6) c=0;
                        if (c) printf("\nEntrez une utilite entre 1 et 5\n\n");
                    }
                    c=1;
                    while (c)
                    {
                        printf("\nEntrez la valeur marchande de l'objet.\n");
                        scanf ("%d",&valeur);
                        if (valeur>=0&&valeur<100000) c=0;
                        if (c) printf("\nEntrez un prix correct\n\n");
                    }
                    printf("\nEntrez la description de l'objet.\n");
                    scanf ("%s",tampon2);

                    printf("\n\nVotre Objet :\n\nNom : %s\nPortee : %d\nDegats : %d\nProtection : %d\nUtilite : %d\nValeur : %d\nDescription : %s\n\nVoulez-vous l'ajouter ?\n",nom,portee,degats,protection,utilite,valeur,tampon2);
                    scanf ("%d",&choix);
                    if (choix)
                    {
                        fseek(fObjet, -3, SEEK_END);
                        fprintf(fObjet,"%s/\t",nom);
                        if (portee<10) fprintf(fObjet,"0");
                        fprintf(fObjet,"%d\t",portee);
                        if (degats<10) fprintf(fObjet,"0");
                        fprintf(fObjet,"%d\t",degats);
                        if (protection<10) fprintf(fObjet,"0");
                        fprintf(fObjet,"%d\t%d\t%s/\t%d\n//",protection,utilite,tampon2,valeur);

                    }
                    printf ("Ajouter un autre objet ?\n");
                    scanf ("%d", &choix);
                }
            break;
            case 2: /*Modifier un objet*/
                while (choix!=0)
                {
                    initialiserTousLesObjets (&tab);
                    for (i=1;i<max-3;i++)
                    {
                        printf ("%d.  %s\n",i, tab[i].nom);
                    }
                    j=0;
                    while (j<1||(j>max-4))
                    {
                        printf("\n\nChoisissez l'objet à éditer\n");
                        scanf ("%d",&j);
                    }
                    while (choix!=8)
                    {
                        objInit(&obj,j);
                        printf ("\n1. Nom : %s\n2. Portée : %c\n3. Dégats : %c\n4. Protection : %c\n5. Utilite : %s\n6. Valeur : %d\n7. Description : %s\n8. Annuler\n\nSélectionnez le paramètre à modifier.\n",obj.nom, '0'+obj.portee, '0'+obj.degats, '0'+obj.protection, getObjetUtiliteNom(&obj),obj.valeur, obj.description);
                        scanf("%d",&choix);
                        switch (choix)
                        {
                            case 1:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez le nouveau nom de cet objet.\n");
                                    scanf("%s",tampon);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fprintf (fTampon,"%s",tampon);
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf (fTampon,"%s",ligne+strlen(obj.nom));
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 2:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouvelle portée de %s.\n",obj.nom);
                                    scanf("%d",&valeur);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=ligne+strlen(obj.nom)+2;
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    if (valeur<10) fprintf (fTampon,"%c",'0');
                                    fprintf (fTampon,"%d",valeur);
                                    fprintf (fTampon,"%s",ligne+(fin-ligne)+2);
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 3:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouveaux dégats de %s.\n",obj.nom);
                                    scanf("%d",&valeur);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=ligne+strlen(obj.nom)+5;
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    if (valeur<10) fprintf (fTampon,"%c",'0');
                                    fprintf (fTampon,"%d",valeur);
                                    fprintf (fTampon,"%s",ligne+(fin-ligne)+2);
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 4:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouvelle protection de %s.\n",obj.nom);
                                    scanf("%d",&valeur);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=ligne+strlen(obj.nom)+8;
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    if (valeur<10) fprintf (fTampon,"%c",'0');
                                    fprintf (fTampon,"%d",valeur);
                                    fprintf (fTampon,"%s",ligne+(fin-ligne)+2);
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 5:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouvelle utilitée de %s.\n1.Arme\n2.Armure\n3.Potion,Nourriture\n4.Objet de quête\n5.Autre\n\n",obj.nom);
                                    scanf("%d",&valeur);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=ligne+strlen(obj.nom)+11;
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    fprintf (fTampon,"%d",valeur);
                                    fprintf (fTampon,"%s",ligne+(fin-ligne)+1);
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 6:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouvelle valeur de %s.\n",obj.nom);
                                    scanf("%d",&valeur);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=ligne+strlen(obj.nom)+15+strlen(obj.description);
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    fprintf (fTampon,"%d",valeur);
                                    fprintf (fTampon,"%c",'\n');
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            case 7:
                                fTampon= fopen("data/Tampon.txt", "w");
                                if (fTampon!=NULL)
                                {
                                    printf("Entrez la nouvelle description de %s.\n",obj.nom);
                                    scanf("%s",tampon);
                                    fseek(fObjet,0, SEEK_SET);
                                    for (i=0;i<j+2;i++)
                                    {
                                        fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                        fprintf(fTampon,"%s",ligne);
                                    }
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fin=strstr (ligne,obj.description);
                                    strncpy (tampon2,ligne,fin-ligne);
                                    tampon2[fin-ligne]='\0';
                                    fprintf (fTampon,"%s",tampon2);
                                    fprintf (fTampon,"%s",tampon);
                                    fprintf (fTampon,"%s",ligne+(fin-ligne)+strlen(obj.description));
                                    while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        fprintf(fTampon,"%s",ligne);
                                    }

                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    fObjet= fopen("data/Objets.txt", "r+");
                                }
                            break;
                            default:
                            break;
                        }
                    }
                    printf ("\n\nModifier un autre objet ?\n");
                    scanf ("%d",&choix);
                }
            break;
            case 3:/*Supprimer un objet*/
                while (choix!=0)
                {
                    initialiserTousLesObjets (&tab);
                    for (i=1;i<max-3;i++)
                    {
                        printf ("%d.  %s\n",i, tab[i].nom);
                    }
                    j=0;
                    while ((j<1)||(j>max-4))
                    {
                        printf("\n\nChoisissez l'objet à supprimer\n");
                        scanf ("%d",&j);
                    }
                    printf ("\nSupprimer %s ?\n",tab[j].nom);
                    scanf ("%d",&valeur);
                    if (valeur)
                    {
                        fTampon=fopen("data/Tampon.txt","w");
                        i=0;
                        fseek(fObjet,0,SEEK_SET);
                        while(fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                        {
                            if (i-2!=j) fprintf(fTampon,"%s",ligne);
                            i++;
                        }
                        fclose (fTampon);
                        fclose (fObjet);
                        copierFichier("data/Tampon.txt","data/Objets.txt");
                        remove("data/Tampon.txt");
                        fObjet=fopen ("data/Objets.txt","r+");
                    }
                    printf ("\nSupprimer un autre objet ?\n");
                    scanf ("%d",&choix);
                }
            break;
            default:
                printf ("\n\n");
            break;
        }
    }
}

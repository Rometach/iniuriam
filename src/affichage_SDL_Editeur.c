#include "affichage_SDL_Editeur.h"


/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

int min (int a,int b)
{
    if (a<=b) return a;
    else return b;
}

int maxi (int a,int b)
{
    if (a>=b) return a;
    else return b;
}

void affChipset(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;
    position.x = 0;
    position.y = 0;

    for(i=ter->defilY;i<getNbrTile(ter); i++)
       {
            tile.w=TILE_LARGEUR;
            tile.h=TILE_HAUTEUR;

            tile.x=getPosX(ter->tabChipset[i]);
            tile.y=getPosY(ter->tabChipset[i]);

            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.w=2;
            position.h=2;
            SDL_FillRect(SDL_GetVideoSurface(),&position,
                         ((getCollision(ter->tabChipset[i]))==0)?
                         SDL_MapRGB(SDL_GetVideoSurface()->format,255,0,0)
                         : SDL_MapRGB(SDL_GetVideoSurface()->format,0,255,0));

            position.x+= TILE_LARGEUR;

            if(position.x>=ter->decalageX*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
           }
        }
            SDL_Flip(ecran);
}

void affEditeur(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    affChipset(ter, ecran);
    position.x = (ter->decalageX+1)*TILE_LARGEUR;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i=0; i<CARTE_LARGEUR*CARTE_HAUTEUR; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>(CARTE_LARGEUR+ter->decalageX)*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=(ter->decalageX+1)*TILE_LARGEUR;
            }
    }
    SDL_Flip(ecran);
}

void affCarte(Terrain* ter, SDL_Surface* ecran)
{
    SDL_Rect position;
    SDL_Rect tile;
    unsigned int i;

    position.x = 0;
    position.y = 0;
    tile.w=TILE_LARGEUR;
    tile.h=TILE_HAUTEUR;

     for(i= 0; i<CARTE_HAUTEUR*CARTE_LARGEUR; i++)
     {
            tile.x=getPosX(ter->tabChipset[ter->carte[i]]);
            tile.y=getPosY(ter->tabChipset[ter->carte[i]]);
            SDL_BlitSurface(ter->chipset, &tile, ecran, &position);

            position.x+= TILE_LARGEUR;
            if(position.x>=CARTE_LARGEUR*TILE_LARGEUR)
            {
                position.y+= TILE_HAUTEUR;
                position.x=0;
            }
    }
    SDL_Flip(ecran);
}

void eventEditeurSDL(Terrain* ter, SDL_Surface* ecran )
{
    int i;
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
            { if(event.key.state==SDL_PRESSED)
                {
                 if(event.key.keysym.sym==SDLK_PAGEUP)  /** Défilement du chipset vers le haut */
                    {
                       if(ter->defilY>0){ ter->defilY-=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_PAGEDOWN)    /** Défilement du chipset vers le bas */
                    {
                        if(ter->defilY<ter->nbrTileChipset-TAILLE_FENETRE_H/TILE_HAUTEUR){ter->defilY+=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_s) /** Sauvegarde de la carte */
                    {
                        terSauvegarde(ter, "data/Cartes/save.map", "data/Chipsets/desertChipset.bmp");
                    }
                    else if(event.key.keysym.sym==SDLK_l) /** Chargement de la carte */
                    {   terLibere(ter);
                        terInit(ter);
                        terCharger(ter, "data/Cartes/save.map");
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
             if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {   ter->tileSel=((event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY)%ter->nbrTileChipset;
                    if(ter->tileSel>=ter->nbrTileChipset) ter->tileSel=ter->nbrTileChipset-1;
                }
                else if(event.button.x>ter->decalageX*TILE_LARGEUR)
                {
                   i=((event.button.y/TILE_HAUTEUR)*CARTE_LARGEUR+event.button.x/TILE_LARGEUR-ter->decalageX-1);

                    if(i>=CARTE_LARGEUR*CARTE_HAUTEUR) i=CARTE_LARGEUR*CARTE_HAUTEUR-1;
                    setCarte(ter, i, ter->tileSel);
                }
            }

            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                if(event.button.x<ter->decalageX*TILE_LARGEUR)
                {
                    i=(event.button.y/TILE_HAUTEUR)*(ter->decalageX)+event.button.x/TILE_LARGEUR+ter->defilY;
                   setCollision(&ter->tabChipset[i], (ter->tabChipset[i].collision+1)%2);
                }
            }
            break;

            case SDL_QUIT:
                continuer = 0;
            break;
        }
        affEditeur(ter, ecran);
    }
}

char eventEditeurObjet()
{
    char action=0;
    char continuer=1;
    SDL_Event event;

    /*SDL_EnableKeyRepeat(10, 10);*/
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        action=1;
                        continuer=0;
                    break;
                    case SDLK_UP:
                        action=2;
                        continuer=0;
                    break;
                    case SDLK_DOWN:
                        action=3;
                        continuer=0;
                    break;
                    case SDLK_RETURN:
                        action=5;
                        continuer=0;
                    default:
                    break;
                }
            break;
            case SDL_QUIT:
                continuer = 0;
            break;
            default:
            break;
        }
    }
    return action;
}

void afficherEditeurObjet (SDL_Surface *ecran,TTF_Font *police)
{
    char action=4,selection,type=1;
    int i,j,nb,choix=0,objet=1,valeur,max,decalage=0,taille, haut=0,bas=9,page;
    char ligne[TAILLE_MAX_FICHIER],tampon[TAILLE_MAX_FICHIER], chaine1 [150], chaine2[150];
    char* fin;
    char ok=0;

    max=getNbObjet();
    char texte_SDL [max-3][150];

    Objet* tab, nouveau;
    FILE *fTampon,*fObjet;

    SDL_Surface *titre=NULL,*nom=NULL, **rectangle=NULL,*texte=NULL, *cadre=NULL;
    SDL_Rect position,position_rect;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    while (action)
    {
        titre = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));
        SDL_FillRect(titre, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

        position.x=TAILLE_FENETRE_L/2-200;
        position.y=TAILLE_FENETRE_H/20;
        SDL_BlitSurface(titre, NULL, ecran, &position);
        SDL_FreeSurface(titre);
        nb=0;
        switch(action)
        {
            case 1:/*Touche Echap*/
                switch (type)
                {
                    case 5:/*Echap lors d'une confirmation*/
                    break;
                    case 6:/*Echap dans le menu de l'objet*/
                        type=3;
                        choix=0;
                    break;
                    default:
                        type=1;
                        choix=0;
                    break;
                }
            break;
            case 2:/*Touche Flèche haut*/
                choix--;
            break;
            case 3:/*Touche Flèche bas*/
                choix++;
            break;
            case 5:/*Touche Entrée*/
                switch (type)
                {
                    case 1:/*Menu Principal*/
                        switch (choix)
                        {
                            case 0:
                                selection=0;
                                choix=0;
                                type=2;/*Accès à Ajouter un objet*/
                            break;
                            case 1:
                                choix=0;
                                type=3;/*Acces à Modifier Objet*/
                            break;
                            case 2:
                                choix=0;
                                type=4;/*Accès à Supprimer Objet*/
                            break;
                            case 3:/*Quitter*/
                                type=0;
                                action=0;
                            break;
                            default:
                            break;
                        }
                    break;
                    case 2:/*Ajouter un objet*/
                        choix=0;
                        selection++;
                    break;
                    case 3:/*Modifier un objet*/
                        type=6;
                        objet=choix+1;
                        choix=0;
                    break;
                    case 4:/*Supprimer*/
                        type=5;
                        selection=1;
                        tab=(Objet*)malloc(sizeof(Objet));
                        objInit(tab,choix+1);
                        objet=choix+1;
                        strcpy(chaine1,"Supprimer ");
                        strcpy(chaine2,getObjetNom2(tab));
                        free(tab);
                        choix=1;
                    break;
                    case 5:/*Confirmer*/
                        switch (selection)
                        {
                            case 1:/*Confirmer Suppression ?*/
                                if (choix==0)
                                {
                                    fTampon=fopen("data/Tampon.txt","w");
                                    fObjet=fopen ("data/Objets.txt","r");
                                    i=0;
                                    while(fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                    {
                                        if (i-2!=objet) fprintf(fTampon,"%s",ligne);
                                        i++;
                                    }
                                    fclose (fTampon);
                                    fclose (fObjet);
                                    copierFichier("data/Tampon.txt","data/Objets.txt");
                                    remove("data/Tampon.txt");
                                    max--;
                                }
                                type=5;
                                strcpy(chaine1,"Supprimer un autre objet");
                                strcpy(chaine2,"");
                                choix=0;
                                selection=2;
                            break;
                            case 2:/*Retour menu Suppression*/
                                if (choix) type= 1;
                                else type=4;
                                choix=0;
                            break;
                            case 3:/*Retour menu Modification*/
                                if (choix) type=1;
                                else type=3;
                                choix=0;
                            break;
                            case 4:/*Retour au menu d'ajout*/
                                if (choix) type=1;
                                else type=2;
                                choix=0;
                                selection=0;
                            break;
                            default:
                            break;
                        }
                    break;
                    case 6: /*Modifier un paramètre d'objet*/
                        if (choix!=7)
                        {
                            type=7;
                            selection=choix;
                        }
                        else
                        {
                            if (ok)
                            {
                                ok=0;
                                strcpy(chaine1,"Ajouter");
                                selection=4;
                            }
                            else
                            {
                                strcpy(chaine1,"Modifier");
                                selection=3;
                            }
                            type=5;

                            strcpy(chaine2," un autre objet");
                        }
                    break;
                    default:
                    break;
                }
            break;
            default:
            break;
        }
        switch (type)
        {
            case 1:/*Menu Principal*/
                nb=4;
                nom = TTF_RenderText_Shaded(police, "Editeur d'Objet", couleur_texte,couleur_rect);

                strcpy(texte_SDL[0],"Ajouter un objet");
                strcpy(texte_SDL[1],"Modifier un objet");
                strcpy(texte_SDL[2],"Supprimer un objet");
                strcpy(texte_SDL[3],"Quitter");

                rectangle=(SDL_Surface**)malloc(4*sizeof(SDL_Surface*));
            break;
            case 2:/*Ajouter un objet*/
                nb=0;

                switch (selection)
                {
                    case 0:
                        strcpy(chaine1,"le nom");
                    break;
                    case 1:
                        strcpy(chaine1,"l'utilite");
                    break;
                    case 2:
                        switch(getObjetUtilite(&nouveau))
                        {
                            case 2:
                                strcpy(chaine1,"le type");
                                strcpy(texte_SDL[0],"1. Casque");
                                strcpy(texte_SDL[1],"2. Plastron");
                                strcpy(texte_SDL[2],"3. Jambieres");
                                strcpy(texte_SDL[3],"4. Gants");
                                strcpy(texte_SDL[4],"5. Chaussures");
                                strcpy(texte_SDL[5],"6. Bouclier");
                                for (i=0;i<6;i++)
                                {
                                    position_rect.x=TAILLE_FENETRE_L/2-250;
                                    position_rect.y=TAILLE_FENETRE_H/4+40*i;
                                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                                    SDL_FreeSurface(texte);
                                }
                            break;
                            default:
                                strcpy(chaine1,"la portee");
                            break;
                        }
                    break;
                    case 3:
                        switch (getObjetUtilite(&nouveau))
                        {
                            case 3:
                                strcpy(chaine1,"l'effet");
                                strcpy(texte_SDL[0],"1. Soin");
                                strcpy(texte_SDL[1],"2. Degats");
                                for (i=0;i<2;i++)
                                {
                                    position_rect.x=TAILLE_FENETRE_L/2-250;
                                    position_rect.y=TAILLE_FENETRE_H/4+40*i;
                                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                                    SDL_FreeSurface(texte);
                                }
                            break;
                            default:
                                strcpy(chaine1,"les degats");
                            break;
                        }
                    break;
                    case 4:
                        switch (getObjetUtilite(&nouveau))
                        {
                            case 3:
                                strcpy(chaine1,"l'impact");
                            break;
                            default:
                                strcpy(chaine1,"la protection");
                            break;
                        }
                    break;
                    case 5:
                        strcpy(chaine1,"la valeur");
                    break;
                    case 6:
                        strcpy(chaine1,"la description");
                    break;
                    default:
                    break;
                }
                sprintf(ligne,"Entrez %s de l'objet.",chaine1);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);
            break;
            case 3:/*Modifier Objet*/
                nb=max-4;
                initialiserTousLesObjets (&tab);

                nom = TTF_RenderText_Shaded(police, "Modifier un objet", couleur_texte,couleur_rect);

                for (i=0;i<max-4;i++)
                {
                    getObjetNom(&tab[i+1],chaine1);
                    strcpy(texte_SDL[i],chaine1);
                }

                free (tab);
                rectangle=(SDL_Surface**)malloc((max-4)*sizeof(SDL_Surface*));
                ok=0;
            break;
            case 4:/*Supprimer Objet*/
                nb=max-4;
                initialiserTousLesObjets (&tab);

                nom = TTF_RenderText_Shaded(police, "Supprimer un objet", couleur_texte,couleur_rect);

                for (i=0;i<max-4;i++)
                {
                    getObjetNom(&tab[i+1],chaine1);
                    strcpy(texte_SDL[i],chaine1);
                }

                free (tab);
                rectangle=(SDL_Surface**)malloc((max-4)*sizeof(SDL_Surface*));
            break;
            case 5:/*Confirmation*/
                nb=2;

                sprintf(ligne,"%s %s ?",chaine1,chaine2);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);

                strcpy(texte_SDL[0],"Oui");
                strcpy(texte_SDL[1],"Non");

                rectangle=(SDL_Surface**)malloc(2*sizeof(SDL_Surface*));
            break;
            case 6:/*Choix du paramètre à modifier*/
                nb=8;
                nom = TTF_RenderText_Shaded(police,"Votre Objet", couleur_texte,couleur_rect);
                tab=(Objet*)malloc(sizeof(Objet));
                objInit(tab,objet);

                getObjetNom(tab,chaine1);
                sprintf(texte_SDL[0],"Nom : %s",chaine1);
                sprintf(texte_SDL[1],"Utilite : %s",getObjetUtiliteNom(tab));
                switch (getObjetUtilite(tab))
                {
                    case 2:
                        sprintf(texte_SDL[2],"Type : %s",getArmureType(tab));
                    break;
                    default:
                        sprintf(texte_SDL[2],"Portee : %d",getObjetPortee(tab));
                    break;
                }
                switch (getObjetUtilite(tab))
                {
                    case 3:
                        sprintf(texte_SDL[3],"Effet : %s",getPotionType(tab));
                    break;
                    default:
                        sprintf(texte_SDL[3],"Degats : %d",getObjetDegats(tab));
                    break;
                }
                switch (getObjetUtilite(tab))
                {
                    case 3:
                        sprintf(texte_SDL[4],"Impact : %d",getObjetProtection(tab));
                    break;
                    default:
                        sprintf(texte_SDL[4],"Protection : %d",getObjetProtection(tab));
                    break;
                }
                sprintf(texte_SDL[5],"Valeur : %d",getObjetValeur(tab));
                getObjetDescription(tab,chaine1);
                sprintf(texte_SDL[6],"Description : %s",chaine1);
                strcpy(texte_SDL[7],"Valider");
                free (tab);
                rectangle=(SDL_Surface**)malloc(8*sizeof(SDL_Surface*));
            break;
            case 7:/*Modification d'un paramètre*/
                nb=0;
                tab=(Objet*)malloc(sizeof(Objet));
                objInit(tab,objet);
                switch (selection)
                {
                    case 0:
                        strcpy(chaine1,"le nom");
                    break;
                    case 1:
                        strcpy(chaine1,"l'utilite");
                    break;
                    case 2:
                        switch (getObjetUtilite(tab))
                        {
                            case 2:
                                strcpy(chaine1,"le type");
                                strcpy(texte_SDL[0],"1. Casque");
                                strcpy(texte_SDL[1],"2. Plastron");
                                strcpy(texte_SDL[2],"3. Jambieres");
                                strcpy(texte_SDL[3],"4. Gants");
                                strcpy(texte_SDL[4],"5. Chaussures");
                                strcpy(texte_SDL[5],"6. Bouclier");
                                for (i=0;i<6;i++)
                                {
                                    position_rect.x=TAILLE_FENETRE_L/2-250;
                                    position_rect.y=TAILLE_FENETRE_H/4+40*i;
                                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                                    SDL_FreeSurface(texte);
                                }
                            break;
                            default:
                                strcpy(chaine1,"la portee");
                            break;
                        }
                    break;
                    case 3:
                        switch (getObjetUtilite(tab))
                        {
                            case 3:
                                strcpy(chaine1,"l'effet");
                                strcpy(texte_SDL[0],"1. Soin");
                                strcpy(texte_SDL[1],"2. Degats");
                                for (i=0;i<2;i++)
                                {
                                    position_rect.x=TAILLE_FENETRE_L/2-250;
                                    position_rect.y=TAILLE_FENETRE_H/4+40*i;
                                    texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                                    SDL_FreeSurface(texte);
                                }
                            break;
                            default:
                                strcpy(chaine1,"les degats");
                            break;
                        }
                    break;
                    case 4:
                        switch (getObjetUtilite(tab))
                        {
                            case 3:
                                strcpy(chaine1,"l'impact");
                        break;
                            default:
                                strcpy(chaine1,"la protection");
                            break;
                        }
                    break;
                    case 5:
                        strcpy(chaine1,"la valeur");
                    break;
                    case 6:
                        strcpy(chaine1,"la description");
                    break;
                    default:
                    break;
                }
                free (tab);

                sprintf(ligne,"Modifier %s de l'objet.",chaine1);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);
            break;
            default:
            break;
        }
        if (action)
        {
            position.x=TAILLE_FENETRE_L/2-100;
            position.y=TAILLE_FENETRE_H/20+25;
            SDL_BlitSurface(nom, NULL, ecran, &position);
            SDL_FreeSurface(nom);
        }
        if (nb==0) choix=0;
        else if (choix==0||choix>nb-1)/*aller à la première page et au premier choix*/
        {
            choix=0;
            haut=0;
            bas=8;
        }
        else if (choix<0)/*aller à la dernière page et au dernier choix*/
        {
            choix=nb-1;
            haut=nb-2;
            bas=nb;
        }
        else if (choix>bas-1)/*avancer d'une page*/
        {
            valeur=(int)strlen(texte_SDL[haut])/19;
            if ((int)strlen(texte_SDL[choix])/19>=valeur) haut+=(int)1+strlen(texte_SDL[choix])/19-valeur;
            else haut++;

            if(valeur>(int)strlen(texte_SDL[choix])/19) bas+=1+valeur;
            else bas+=(int)1+strlen(texte_SDL[choix])/19;
        }
        else if (choix<haut)/*reculer d'une page*/
        {
            haut--;
            /*bas--;*/
        }

        if (nb>4)page=maxi(haut,0);
        else
        {
            haut =0;
            page =0;
        }
        decalage=0;
        for (i=page;i<min(bas,nb);i++)/*Page visible*/
        {
            if (i==choix) /*Affichage du cadre*/
            {
                cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
                SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                position_rect.x=TAILLE_FENETRE_L/2-155;
                position_rect.y=TAILLE_FENETRE_H/3-5+(50+(100/nb))*(i-haut)+50*(decalage);
                SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                SDL_FreeSurface(cadre);
            }

            taille=0;
            position_rect.x=TAILLE_FENETRE_L/2-150;
            position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-haut)+50*(decalage);
            if (strlen(texte_SDL[i])>18)
            {
                strcpy(chaine1,texte_SDL[i]);
                while (strlen(chaine1)>=18)
                {
                    taille++;
                    j=17;
                    while (j>=1&&chaine1[j]!=' ') j--;
                    if (j!=0)
                    {
                        valeur=j;
                        strncpy(chaine2,chaine1,valeur);
                        chaine2[valeur]='\0';
                    }
                    else
                    {
                        strncpy(chaine2,chaine1,17);
                        chaine2[17]='-';
                        chaine2[18]='\0';

                    }
                    if (i==choix) /*Affichage d'un cadre suplémentaire*/
                    {
                        cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
                        SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                        position_rect.x=TAILLE_FENETRE_L/2-155;
                        position_rect.y=TAILLE_FENETRE_H/3-5+(50+(100/nb))*(i-haut)+50*(decalage+taille);
                        SDL_BlitSurface(cadre, NULL, ecran, &position_rect);
                        SDL_FreeSurface(cadre);
                        position_rect.x+=5;
                        position_rect.y-=45;
                    }

                    rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
                    SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
                    SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect);
                    SDL_FreeSurface(rectangle[i]);

                    position_rect.x+= 25;
                    texte=TTF_RenderText_Shaded(police, chaine2, couleur_texte,couleur_rect);
                    SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                    SDL_FreeSurface(texte);
                    position_rect.x-= 25;
                    position_rect.y+=50;
                    for (j=0;j<strlen(texte_SDL[i])-valeur+1;j++)
                    {
                        chaine1[j]=chaine1[valeur+j];
                    }
                }
                strcpy(texte_SDL[i],chaine1);
                decalage+=taille;
            }
            rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

            position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-haut)+50*(decalage);
            SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect);
            SDL_FreeSurface(rectangle[i]);

            position_rect.x+= 25;
            position_rect.y=TAILLE_FENETRE_H/3+(50+(100/nb))*(i-haut)+50*(decalage);
            texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
            SDL_BlitSurface(texte, NULL, ecran, &position_rect);
            SDL_FreeSurface(texte);
            if (page+decalage<haut+9)page++;
        }
        bas=page;
        SDL_Flip(ecran);
        if (nb==0&&action)/*Besoin d'un scanf*/
        {
            switch  (selection)
            {
                case 0:
                    scanfSDL(tampon,ecran,30,&action,police,0);
                break;
                case 1:
                    strcpy(texte_SDL[0],"1. Arme");
                    strcpy(texte_SDL[1],"2. Armure");
                    strcpy(texte_SDL[2],"3. Potion ou nourriture");
                    strcpy(texte_SDL[3],"4. Objet de quete");
                    strcpy(texte_SDL[4],"5. Autre");
                    for (i=0;i<5;i++)
                    {
                        position_rect.x=TAILLE_FENETRE_L/2-250;
                        position_rect.y=TAILLE_FENETRE_H/4+40*i;
                        texte=TTF_RenderText_Shaded(police, texte_SDL[i], couleur_texte,couleur_rect);
                        SDL_BlitSurface(texte, NULL, ecran, &position_rect);
                        SDL_FreeSurface(texte);
                    }
                    SDL_Flip(ecran);
                    scanfSDL(tampon,ecran,1,&action,police,1);
                    valeur=atoi(tampon);
                break;
                case 5:
                    scanfSDL(tampon,ecran,7,&action,police,1);
                    valeur=atoi(tampon);
                break;
                case 6:
                    scanfSDL(tampon,ecran,150,&action,police,0);
                break;
                default:
                    scanfSDL(tampon,ecran,2,&action,police,1);
                    valeur=atoi(tampon);
                break;
            }

            if (type==2)/*Ajout d'un objet*/
            {
                switch (action)
                {
                    case 1:/*Echap*/
                        action=0;
                        type=1;
                        choix=0;
                        ok=1;
                    break;
                    case 2:/*Entrée*/
                        switch (selection)
                        {
                            case 0:/*Ajout du nom*/
                                ok=1;
                                initialiserTousLesObjets(&tab);
                                for(i=1;i<max-3;i++)
                                {
                                    getObjetNom(&tab[i],chaine1);
                                    if (strcmp(chaine1,tampon)==0)
                                    {
                                        ok=0;
                                    }
                                }
                                if (ok)
                                {
                                    setObjetNom (&nouveau,tampon);
                                }
                                else selection--;
                                free(tab);
                            break;
                            case 2:/*Ajout de la portee*/
                                setObjetPortee (&nouveau,valeur);
                            break;
                            case 3:/*Ajout des dégats*/
                                setObjetDegats (&nouveau,valeur);
                            break;
                            case 4:/*Ajout de la protection*/
                                setObjetProtection (&nouveau,valeur);
                            break;
                            case 1:/*Ajout de l'utilité*/
                                setObjetUtilite (&nouveau,valeur);
                            break;
                            case 5:/*Ajout de la valeur*/
                                setObjetValeur (&nouveau,valeur);
                            break;
                            case 6:/*Ajout de la description*/
                                setObjetDescription (&nouveau,tampon);
                                fObjet=fopen("data/Objets.txt","r+");
                                fseek(fObjet, -4, SEEK_END);
                                getObjetNom(&nouveau,chaine1);
                                fprintf(fObjet,"\n%s/\t",chaine1);
                                    if ((int)getObjetPortee(&nouveau)<10) fprintf(fObjet,"0");
                                    fprintf(fObjet,"%d\t",getObjetPortee(&nouveau));
                                    if ((int)getObjetDegats(&nouveau)<10) fprintf(fObjet,"0");
                                    fprintf(fObjet,"%d\t",getObjetDegats(&nouveau));
                                    if ((int)getObjetProtection(&nouveau)<10) fprintf(fObjet,"0");
                                    getObjetDescription(&nouveau,chaine1);
                                    fprintf(fObjet,"%d\t%d\t%s/\t%d\n//",(int)getObjetProtection(&nouveau),(int)getObjetUtilite(&nouveau),chaine1,(int)getObjetValeur(&nouveau));
                                    fclose (fObjet);
                                    max++;
                            break;
                            default:
                            break;
                        }
                    break;
                    default:/*Quitter ou erreur*/
                        action=0;
                        ok=0;
                    break;
                }
                if (action&&selection<6) /*Poursuite de l'ajout*/
                {
                    action=5;
                    type=2;
                }
                else if (action) /*Retour menu modif objet, ajout terminé*/
                {
                    action=5;
                    type=3;
                    choix=max-5;
                }
            }
            else if (type==7)/*Modification d'un paramètre de l'objet*/
            {
                switch (action)
                {
                    case 1:/*Echap*/
                        action=5;
                        type=3;
                        choix=objet-1;
                    break;
                    case 2:/*Entrée*/
                        tab=(Objet*)malloc(sizeof(Objet));
                        objInit(tab,objet);
                        fObjet= fopen("data/Objets.txt", "r");
                        fTampon= fopen("data/Tampon.txt", "w");
                        for (i=0;i<objet+2;i++)
                        {
                            fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                            fprintf(fTampon,"%s",ligne);
                        }
                        switch (selection)
                        {
                            case 0:/*Modifier nom*/
                                fprintf (fTampon,"%s",tampon);
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                fprintf (fTampon,"%s",ligne+strlen(chaine1));
                                while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                {
                                    fprintf(fTampon,"%s",ligne);
                                }

                                fclose (fTampon);
                                fclose (fObjet);
                                copierFichier("data/Tampon.txt","data/Objets.txt");
                                remove("data/Tampon.txt");
                            break;
                            case 2:/*Modifier Portee*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                fin=ligne+strlen(chaine1)+2;
                                strncpy (tampon,ligne,fin-ligne);
                                tampon[fin-ligne]='\0';
                                fprintf (fTampon,"%s",tampon);
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
                            break;
                            case 3:/*Modifier Degats*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                fin=ligne+strlen(chaine1)+5;
                                strncpy (tampon,ligne,fin-ligne);
                                tampon[fin-ligne]='\0';
                                fprintf (fTampon,"%s",tampon);
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
                            break;
                            case 4:/*Modifier Protection*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                fin=ligne+strlen(chaine1)+8;
                                strncpy (tampon,ligne,fin-ligne);
                                tampon[fin-ligne]='\0';
                                fprintf (fTampon,"%s",tampon);
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
                            break;
                            case 1:/*Modifier utilite*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                fin=ligne+strlen(chaine1)+11;
                                strncpy (tampon,ligne,fin-ligne);
                                tampon[fin-ligne]='\0';
                                fprintf (fTampon,"%s",tampon);
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
                            break;
                            case 5:/*Modifier valeur*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetNom(tab,chaine1);
                                getObjetDescription(tab,chaine2);
                                fin=ligne+strlen(chaine1)+15+strlen(chaine2);
                                strncpy (tampon,ligne,fin-ligne);
                                tampon[fin-ligne]='\0';
                                fprintf (fTampon,"%s",tampon);
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
                            break;
                            case 6:/*Modifier Description*/
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                getObjetDescription(tab,chaine1);
                                fin=strstr (ligne,chaine1);
                                strncpy (chaine1,ligne,fin-ligne);
                                chaine1[fin-ligne]='\0';
                                fprintf (fTampon,"%s",chaine1);
                                fprintf (fTampon,"%s",tampon);
                                fprintf (fTampon,"%s",ligne+(fin-ligne)+strlen(chaine1));
                                while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                {
                                    fprintf(fTampon,"%s",ligne);
                                }

                                fclose (fTampon);
                                fclose (fObjet);
                                copierFichier("data/Tampon.txt","data/Objets.txt");
                                remove("data/Tampon.txt");
                            break;
                            default:
                                fclose (fTampon);
                                fclose (fObjet);
                            break;
                        }
                        free (tab);
                    break;
                    default:/*Quitter ou erreur*/
                        action=0;
                    break;
                }
                if (action) /*Retour menu modif objet si aucune erreur*/
                {
                    action=5;
                    type=3;
                    choix=objet-1;
                }
            }
        }
        else if (action&&nb)
        {
            action=eventEditeurObjet();
            free (rectangle);
        }

        if (ok&&action==0)/*Touche Echap*/
        {
            action=1;
            ok=0;
        }
    }
}

void editerObjet (SDL_Surface *ecran,TTF_Font *police)
{
    ecran=SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Editeur d'Objet", NULL);
    afficherEditeurObjet(ecran,police);/*Affichage de l'écran principal*/
}

void editerCarte (SDL_Surface *ecran,Terrain* terrain)
{
    terInit(terrain);
    terRemplirStruct(terrain);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE_L+TILE_LARGEUR*terrain->decalageX, TAILLE_FENETRE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Editeur de Carte", NULL);

    eventEditeurSDL(terrain, ecran);

    terLibere(terrain);
}

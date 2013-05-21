#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "affichage_SDL_Editeur.h"
#include "terrain.h"
#include "tile.h"
#include "competence.h"
#include "perso_Editeur.h"
#include "objet_Editeur.h"
#include "constante.h"
#include "scanf_SDL.h"

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

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
            printf("%d ",ter->carte[i]);

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
                        if(ter->defilY<ter->nbrTileChipset-TAILLE_FENETRE/TILE_HAUTEUR){ter->defilY+=ter->decalageX;}
                    }
                    else if(event.key.keysym.sym==SDLK_s) /** Sauvegarde de la carte */
                    {
                        terSauvegarde(ter, "data/Cartes/save.map", "data/Chipsets/HOTEL02.bmp");
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

char eventEditeurObjet(SDL_Surface *ecran)
{
    char action=0;
    char continuer=1;
    SDL_Event event;

    //SDL_EnableKeyRepeat(10, 10);
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
                    case SDLK_BACKSPACE:
                        action=4;
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

void afficherEditeurObjet (SDL_Surface *ecran, char type,TTF_Font *police)
{
    char action=6,selection;
    int i,nb,choix=0,page=0,objet,valeur,max=0;
    char ligne[TAILLE_MAX_FICHIER],tampon[TAILLE_MAX_FICHIER], chaine1 [150], chaine2[150];
    char* fin;
    char ok=0;
    Objet* tab, nouveau;
    FILE *fTampon,*fObjet;


    SDL_Surface *titre=NULL,*nom=NULL, **rectangle=NULL,**texte=NULL, *cadre=NULL;
    SDL_Rect position,*position_rect=NULL;
    SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};

    titre = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
    cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);

    while (action)
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));
        SDL_FillRect(titre, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
        SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

        position.x=TAILLE_FENETRE/2-200;
        position.y=TAILLE_FENETRE/20;
        SDL_BlitSurface(titre, NULL, ecran, &position);
        nb=0;
        switch(action)
        {
            case 1:

            break;
            case 2:
                choix--;
            break;
            case 3:
                choix++;
            break;
            case 4:
            break;
            case 5:
                switch (type)
                {
                    case 1://Menu Principal
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
                        page=0;
                        choix=0;
                        selection++;
                    break;
                    case 3:/*Modifier un objet*/
                        page=0;
                        type=6;
                        objet=choix+1;
                        choix=0;
                    break;
                    case 4:/*Supprimer*/
                        page=0;
                        type=5;
                        selection=1;
                        tab=(Objet*)malloc(sizeof(Objet));
                        objInit(tab,choix+1);
                        objet=choix+1;
                        strcpy(chaine1,"Supprimer ");
                        strcpy(chaine2,tab->nom);
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
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
                texte=(SDL_Surface**)malloc(4*sizeof(SDL_Surface*));
                texte[0]=TTF_RenderText_Shaded(police, "Ajouter un objet", couleur_texte,couleur_rect);
                texte[1]=TTF_RenderText_Shaded(police, "Modifier un objet", couleur_texte,couleur_rect);
                texte[2]=TTF_RenderText_Shaded(police, "Supprimer un objet", couleur_texte,couleur_rect);
                texte[3]=TTF_RenderText_Shaded(police, "Quitter", couleur_texte,couleur_rect);

                position_rect=(SDL_Rect*)malloc(4*sizeof(SDL_Rect));
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
                        strcpy(chaine1,"la portee");
                    break;
                    case 2:
                        strcpy(chaine1,"les degats");
                    break;
                    case 3:
                        strcpy(chaine1,"la protection");
                    break;
                    case 4:
                        strcpy(chaine1,"l'utilite");
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
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
            break;
            case 3:/*Modifier Objet*/
                max=getNbObjet();
                nb=max-4;
                initialiserTousLesObjets (&tab);

                nom = TTF_RenderText_Shaded(police, "Modifier un objet", couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                texte=(SDL_Surface**)malloc((max-3)*sizeof(SDL_Surface*));
                for (i=0;i<max-4;i++)
                {
                    texte[i]=TTF_RenderText_Shaded(police, tab[i+1].nom, couleur_texte,couleur_rect);
                }

                free (tab);
                position_rect=(SDL_Rect*)malloc((max-4)*sizeof(SDL_Rect));
                rectangle=(SDL_Surface**)malloc((max-4)*sizeof(SDL_Surface*));
            break;
            case 4:/*Supprimer Objet*/
                max=getNbObjet();
                nb=max-4;
                initialiserTousLesObjets (&tab);

                nom = TTF_RenderText_Shaded(police, "Supprimer un objet", couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                texte=(SDL_Surface**)malloc((max-3)*sizeof(SDL_Surface*));
                for (i=0;i<max-4;i++)
                {
                    texte[i]=TTF_RenderText_Shaded(police, tab[i+1].nom, couleur_texte,couleur_rect);
                }

                free (tab);
                position_rect=(SDL_Rect*)malloc((max-4)*sizeof(SDL_Rect));
                rectangle=(SDL_Surface**)malloc((max-4)*sizeof(SDL_Surface*));
            break;
            case 5:/*Confirmation*/
                nb=2;

                sprintf(ligne,"%s %s ?",chaine1,chaine2);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                texte=(SDL_Surface**)malloc(2*sizeof(SDL_Surface*));
                texte[0]=TTF_RenderText_Shaded(police, "Oui", couleur_texte,couleur_rect);
                texte[1]=TTF_RenderText_Shaded(police, "Non", couleur_texte,couleur_rect);

                position_rect=(SDL_Rect*)malloc(2*sizeof(SDL_Rect));
                rectangle=(SDL_Surface**)malloc(2*sizeof(SDL_Surface*));
            break;
            case 6:/*Choix du paramètre à modifier*/
                nb=8;
                nom = TTF_RenderText_Shaded(police,"Votre Objet", couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);

                tab=(Objet*)malloc(sizeof(Objet));
                objInit(tab,objet);
                texte=(SDL_Surface**)malloc(8*sizeof(SDL_Surface*));
                sprintf(ligne,"Nom : %s",tab->nom);
                texte[0]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Portee : %d",tab->portee);
                texte[1]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Degats : %d",tab->degats);
                texte[2]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Protection : %d",tab->protection);
                texte[3]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Utilite : %s",getObjetUtiliteNom(tab));
                texte[4]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Valeur : %d",tab->valeur);
                texte[5]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                sprintf(ligne,"Description : %s",tab->description);
                texte[6]=TTF_RenderText_Shaded(police, ligne, couleur_texte,couleur_rect);
                texte[7]=TTF_RenderText_Shaded(police, "Annuler", couleur_texte,couleur_rect);

                free (tab);
                position_rect=(SDL_Rect*)malloc(8*sizeof(SDL_Rect));
                rectangle=(SDL_Surface**)malloc(8*sizeof(SDL_Surface*));
            break;
            case 7:/*Modification d'un paramètre*/
                nb=0;
                switch (selection)
                {
                    case 0:
                        strcpy(chaine1,"le nom");
                    break;
                    case 1:
                        strcpy(chaine1,"la portee");
                    break;
                    case 2:
                        strcpy(chaine1,"les degats");
                    break;
                    case 3:
                        strcpy(chaine1,"la protection");
                    break;
                    case 4:
                        strcpy(chaine1,"l'utilite");
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
                sprintf(ligne,"Modifier %s de l'objet.",chaine1);
                nom = TTF_RenderText_Shaded(police,ligne, couleur_texte,couleur_rect);
                position.x=TAILLE_FENETRE/2-100;
                position.y=TAILLE_FENETRE/20+25;
                SDL_BlitSurface(nom, NULL, ecran, &position);
                SDL_FreeSurface(nom);
            break;
            default:
            break;
        }
        if (nb==0) choix=0;
        else if (choix<0)/*aller à la dernière page et au dernier choix*/
        {
            choix=nb-1;
            page=(nb-1-(nb-1)%9)/9;
        }
        else if (choix>nb-1)/*aller à la première page et au premier choix*/
        {
            choix=0;
            page=0;
        }
        else if (choix%9==0)/*avancer d'une page*/
        {
            page=choix/9;
        }
        else if (choix<page*9)/*reculer d'une page*/
        {
            page--;
        }

        if (nb==0) /*Cas où on a besoin d'un scanf*/
        {
            position_rect=(SDL_Rect*)malloc(sizeof(SDL_Rect));
            rectangle=(SDL_Surface**)malloc(sizeof(SDL_Surface*));
            *rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(*rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
            position_rect->x=TAILLE_FENETRE/2-250;
            position_rect->y=TAILLE_FENETRE/3+150;
            SDL_BlitSurface(*rectangle, NULL, ecran, position_rect);
            SDL_FreeSurface(*rectangle);
        }
        else /*Affichage du cadre*/
        {
            position_rect[0].x=TAILLE_FENETRE/2-155;
            position_rect[0].y=TAILLE_FENETRE/3-5+(50+(100/nb))*(choix-page*9);
            SDL_BlitSurface(cadre, NULL, ecran, &position_rect[0]);
        }

        for (i=page*9;i<nb;i++)/*Page visible*/
        {
            rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
            position_rect[i].x=TAILLE_FENETRE/2-150;
            position_rect[i].y=TAILLE_FENETRE/3+(50+(100/nb))*(i-page*9);
            SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect[i]);
            SDL_FreeSurface(rectangle[i]);

            position_rect[i].x+= 25;
            position_rect[i].y=TAILLE_FENETRE/3+(50+(100/nb))*(i-page*9);
            SDL_BlitSurface(texte[i], NULL, ecran, &position_rect[i]);
            SDL_FreeSurface(texte[i]);
        }
        for (i=0;i<page*9;i++)/*Pages invisibles*/
        {
            rectangle[i]= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
            SDL_FillRect(rectangle[i], NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
            position_rect[i].x=TAILLE_FENETRE/2-150;
            position_rect[i].y=TAILLE_FENETRE/3+(50+(100/nb))*(i+page*9);
            SDL_BlitSurface(rectangle[i], NULL, ecran, &position_rect[i]);
            SDL_FreeSurface(rectangle[i]);

            position_rect[i].x+= 25;
            position_rect[i].y=TAILLE_FENETRE/3+(50+(100/nb))*(i+page*9);
            SDL_BlitSurface(texte[i], NULL, ecran, &position_rect[i]);
            SDL_FreeSurface(texte[i]);
        }

        SDL_Flip(ecran);
        if (nb==0&&action)/*Besoin d'un scanf*/
        {
            switch  (selection)
            {
                case 0:
                    scanfSDL(tampon,ecran,30,&action,police,0);
                break;
                case 4:
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

            if (type==2)
            {
                switch (action)
                {
                    case 1:/*Echap*/
                    break;
                    case 2:/*Entrée*/
                        switch (selection)
                        {
                            case 0:/*Ajout du nom*/
                                ok=1;
                                max=getNbObjet();
                                tab=(Objet*)malloc(max*sizeof(Objet));
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
                                free(tab);
                            break;
                            case 1:/*Ajout de la portee*/
                                setObjetPortee (&nouveau,valeur);
                            break;
                            case 2:/*Ajout des dégats*/
                                setObjetDegats (&nouveau,valeur);
                            break;
                            case 3:/*Ajout de la protection*/
                                setObjetProtection (&nouveau,valeur);
                            break;
                            case 4:/*Ajout de l'utilité*/
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
                                    fprintf(fObjet,"%d\t%d\t%s/\t%d\n//",(int)getObjetProtection(&nouveau),(int)getObjetUtilite(&nouveau),getObjetDescription(&nouveau),(int)getObjetValeur(&nouveau));
                                    fclose (fObjet);
                            break;
                            default:
                            break;
                        }
                    break;
                    default:/*Quitter ou erreur*/
                        action=0;
                    break;
                }
                if (action&&selection<6) /*Poursuite de l'ajout*/
                {
                    action=5;
                    type=2;
                }
                else if (action) /*Retour menu modif objet, ajout terminé*/
                {
                    max=getNbObjet();
                    action=5;
                    type=3;
                    choix=max-4;
                }
            }
            else if (type==7)
            {
                switch (action)
                {
                    case 1:/*Echap*/
                    break;
                    case 2:/*Entrée*/
                        tab=(Objet*)malloc(sizeof(Objet));
                        objInit(tab,objet);
                        fObjet= fopen("data/Objets.txt", "r");
                        fTampon= fopen("data/Tampon.txt", "w");
                        switch (selection)
                        {
                            case 0:/*Modifier nom*/
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fprintf (fTampon,"%s",tampon);
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fprintf (fTampon,"%s",ligne+strlen(tab->nom));
                                while (fgets(ligne,TAILLE_MAX_FICHIER,fObjet)!=NULL)
                                {
                                    fprintf(fTampon,"%s",ligne);
                                }

                                fclose (fTampon);
                                fclose (fObjet);
                                copierFichier("data/Tampon.txt","data/Objets.txt");
                                remove("data/Tampon.txt");
                            break;
                            case 1:/*Modifier Portee*/
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=ligne+strlen(tab->nom)+2;
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
                            case 2:/*Modifier Degats*/
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=ligne+strlen(tab->nom)+5;
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
                            case 3:/*Modifier Protection*/
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=ligne+strlen(tab->nom)+8;
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
                            case 4:/*Modifier utilite*/
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=ligne+strlen(tab->nom)+11;
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
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=ligne+strlen(tab->nom)+15+strlen(tab->description);
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
                                for (i=0;i<objet+2;i++)
                                {
                                    fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                    fprintf(fTampon,"%s",ligne);
                                }
                                fgets (ligne,TAILLE_MAX_FICHIER,fObjet);
                                fin=strstr (ligne,tab->description);
                                strncpy (chaine1,ligne,fin-ligne);
                                chaine1[fin-ligne]='\0';
                                fprintf (fTampon,"%s",chaine1);
                                fprintf (fTampon,"%s",tampon);
                                fprintf (fTampon,"%s",ligne+(fin-ligne)+strlen(tab->description));
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
        else if (action&&nb) action=eventEditeurObjet(ecran);
    }
    free (rectangle);
    free (position_rect);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(cadre);
}

void editerObjet ()
{
    SDL_Surface* ecran = NULL;
    TTF_Font *police = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    police = TTF_OpenFont("data/Jester.ttf", 30);
    ecran=SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE_OBJET, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Editeur d'Objet", NULL);
    afficherEditeurObjet(ecran,1,police);/*Affichage de l'écran principal*/

    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();
}

void editerCarte ()
{
    Terrain terrain;
    SDL_Surface* ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(TAILLE_FENETRE, TAILLE_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Iniuriam", NULL);

    terInit(&terrain);
    terRemplirStruct(&terrain);

    affChipset(&terrain, ecran);
    affEditeur(&terrain, ecran);
    eventEditeurSDL(&terrain, ecran);

    terLibere(&terrain);
    SDL_Quit();
}

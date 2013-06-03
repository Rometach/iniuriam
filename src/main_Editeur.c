#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "affichage_SDL_Editeur.h"

    int main(int argc, char **argv)
    {
        char action=4;
        int choix=0,i;
        SDL_Surface* ecran = NULL,*titre=NULL,*nom=NULL,*texte=NULL,*rectangle=NULL,*cadre;
        TTF_Font *police = NULL;
        SDL_Rect position;
        SDL_Color couleur_texte= {255, 255, 255},couleur_rect= {10, 10, 10};
        Terrain terrain;

        SDL_Init(SDL_INIT_VIDEO);
        SDL_WM_SetCaption("Editeur",NULL);
        ecran=SDL_SetVideoMode(TAILLE_FENETRE_L, TAILLE_FENETRE_H, 32, SDL_HWSURFACE);
        TTF_Init();
        police = TTF_OpenFont("data/Jester.ttf", 30);

        titre = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 100, 32, 0, 0, 0, 0);
        SDL_FillRect(titre, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));

        nom = TTF_RenderText_Shaded(police, "Editeur", couleur_texte,couleur_rect);

        cadre = SDL_CreateRGBSurface(SDL_HWSURFACE, 310, 60, 32, 0, 0, 0, 0);
        SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));

        rectangle= SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 50, 32, 0, 0, 0, 0);
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 10, 10, 10));
        while (action)
        {
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 6, 29, 38));
            position.x=TAILLE_FENETRE_L/2-200;
            position.y=TAILLE_FENETRE_H/20;
            SDL_BlitSurface(titre, NULL, ecran, &position);
            position.x+=100;
            position.y+=25;
            SDL_BlitSurface(nom, NULL, ecran, &position);

            switch(action)
            {
                case 2:
                    choix--;
                break;
                case 3:
                    choix++;
                break;
                case 5:
                    switch (choix)
                    {
                        case 0:/*Editeur de cartes*/
                            editerCarte(ecran,&terrain);
                            action=0;
                        break;
                        case 1:/*Editeur d'Objet*/
                            editerObjet(ecran,police);
                            action=0;
                        break;
                        case 2:/*Quitter*/
                            action=0;
                        break;
                    }
                break;
                default:
                break;
            }

            if (choix<0)choix=2;
            else if (choix>2)choix=0;

            position.x=TAILLE_FENETRE_L/2-155;
            position.y=TAILLE_FENETRE_H/3+(50+(100/3))*choix-5;
            SDL_BlitSurface(cadre, NULL, ecran, &position);

            position.x+=5;
            for (i=0;i<3;i++)
            {
                position.y=TAILLE_FENETRE_H/3+(50+(100/3))*i;
                SDL_BlitSurface(rectangle, NULL, ecran, &position);
            }

            texte=TTF_RenderText_Shaded(police,"Editer Carte", couleur_texte,couleur_rect);
            position.x=TAILLE_FENETRE_L/2-150;
            position.y=TAILLE_FENETRE_H/3;
            SDL_BlitSurface(texte, NULL, ecran, &position);
            SDL_FreeSurface(texte);

            texte=TTF_RenderText_Shaded(police,"Editer Objet", couleur_texte,couleur_rect);
            position.y+=50+100/3;
            SDL_BlitSurface(texte, NULL, ecran, &position);
            SDL_FreeSurface(texte);

            texte=TTF_RenderText_Shaded(police,"Quitter", couleur_texte,couleur_rect);
            position.y+=50+100/3;
            SDL_BlitSurface(texte, NULL, ecran, &position);
            SDL_FreeSurface(texte);

            SDL_Flip(ecran);
            if (action) action=eventEditeurObjet();
        }
        TTF_CloseFont(police);
        TTF_Quit();
        SDL_FreeSurface(nom);
        SDL_FreeSurface(titre);
        SDL_FreeSurface(cadre);
        SDL_FreeSurface(rectangle);
        SDL_FreeSurface(ecran);
        SDL_Quit();
        return 0;
    }


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
* \author RODARIE Dimitri, VERSAEVEL Romain, FLORES Isabelle
*/

#define TAILLE_MAX 22

char deplacerCase (int y, char tab [TAILLE_MAX])
{
    if (tab [y]==0||tab [y]==2||tab[y]>=7) return 0;
    else return 1;
}

char testRetour (int x, char tab [TAILLE_MAX])
{
    if ((tab[x-1]>=7&&tab[x-2]==8)||(tab[x+1]>=8&&tab[x+2]==8)) return 0;
    else return 1;
}

void getColonne(int col, char tab[TAILLE_MAX][TAILLE_MAX], char*tamp)
{
    int i;
    for(i=0;i<TAILLE_MAX; i++)
    {
        tamp[i] = tab[i][col];
    }
}

char min (char a, char b)
{
    if (a-b>0) return b;
    else return a;
}

void afficherTab2D (char tab[TAILLE_MAX][TAILLE_MAX])
{
    int i,j;
    for (i=0;i<TAILLE_MAX;i++)
    {
        for (j=0;j<TAILLE_MAX;j++)
        {
            printf("%d",tab[i][j]);
        }
        printf("\n");
    }
}

char chercher2 (char tab[TAILLE_MAX][TAILLE_MAX],int x, int y)
{
    if (tab[x][y-1]==2) return 1; /* 2 à gauche*/
    else if (tab[x-1][y]==2) return 2; /*2 en haut*/
    else if (tab[x+1][y]==2) return 3;/*2 à droite*/
    else if (tab[x][y+1]==2) return 4;/*2 en bas*/
    else return 0;
}

void tunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX], int i)
{
    char tamp [TAILLE_MAX];
    getColonne(y, tab,tamp);
    switch (i)
    {
        case 0:/*Déplacement en bas*/
            if (deplacerCase(y-1,tab[x])!=0&&tab [x][y-1]!=3) tab [x][y-1]=7;

            if (deplacerCase(y+1,tab[x])!=0&&tab[x][y+1]!=3) tab[x][y+1]=7;

            if (deplacerCase(x-1,tamp)!=0&&tab[x-1][y]!=3) tab[x-1][y]=7;
            break;
        case 1:/*Déplacement à droite*/
            if (deplacerCase(y-1,tab[x])!=0&&tab [x][y-1]!=3) tab [x][y-1]=7;

            if (deplacerCase(x-1,tamp)!=0&&tab[x-1][y]!=3) tab[x-1][y]=7;

            if (deplacerCase(x+1,tamp)!=0&&(tab[x+1][y]!=3)) tab[x+1][y]=7;

            break;
        case 2:/*Déplacement en haut*/
            if (deplacerCase(y+1,tab[x])!=0&&tab [x][y+1]!=3) tab [x][y+1]=7;

            if (deplacerCase(y+1,tab[x])!=0&&tab[x][y+1]!=3) tab[x][y+1]=7;

            if (deplacerCase(x+1,tamp)!=0&&tab[x+1][y]!=3) tab[x+1][y]=7;
            break;
        case 3:/*Déplacement à gauche*/
            if ((deplacerCase(y+1,tab[x])!=0)&&(tab [x][y+1]!=3)) tab [x][y+1]=7;

            if ((deplacerCase(x-1,tamp)!=0)&&tab[x-1][y]!=3) tab[x-1][y]=7;

            if (deplacerCase(x+1,tamp)!=0&&tab[x+1][y]!=3) tab[x+1][y]=7;
            break;
        default: break;
    }
}

void reinitTunnel (int x, int y, char tab [TAILLE_MAX][TAILLE_MAX])
{
    if (tab[x-1][y]==7)tab[x-1][y]=1;
    else if (tab[x-1][y]==9)tab[x-1][y]=0;

    if (tab[x+1][y]==7)tab[x+1][y]=1;
    else if (tab[x+1][y]==7)tab[x+1][y]=0;

    if (tab[x][y-1]==7)tab[x][y-1]=1;
    else if (tab[x][y-1]==7)tab[x][y-1]=0;

    if (tab[x][y+1]==7)tab[x][y+1]=1;
    else if (tab[x][y+1]==7)tab[x][y+1]=0;
}

char quatresChemins (char droite, char haut, char bas, char gauche)
{
    char i=0,j=0;

    if ((gauche==0)&&(droite==0)&&(haut==0)&&(bas==0)) return 0;
    else if ((gauche==0)&&(bas==0)&&(haut==0)) return 1;
    else if ((gauche==0)&&(droite==0)&&(bas==0)) return 2;
    else if ((gauche==0)&&(droite==0)&&(haut==0)) return 3;
    else if ((droite==0)&&(haut==0)&&(bas==0)) return 4;
    else if ((bas==0)&&(gauche==0))
    {
        if (droite==min(droite,haut)) return 1;
        else return 2;
    }
    else if ((gauche==0)&&(haut==0))
    {
        if (droite==min(droite,bas)) return 1;
        else return 3;
    }
    else if ((bas==0)&&(haut==0))
    {
        if (droite==min(droite,gauche)) return 1;
        else return 4;
    }
    else if ((droite==0)&&(gauche==0))
    {
        if (haut==min(haut,bas)) return 2;
        else return 3;
    }
    else if ((droite==0)&&(bas==0))
    {
        if (haut==min(haut,gauche)) return 2;
        else return 4;
    }
    else if ((droite==0)&&(haut==0))
    {
        if (bas==min(bas,gauche)) return 3;
        else return 4;
    }
    else if (gauche==0)
    {
        i=min (droite,haut);
        i=min (i,bas);
        if (i==droite)return droite;
        else if (i==haut) return haut;
        else return bas;
    }
    else if (bas==0)
    {
        i=min (droite,haut);
        i=min (i,gauche);
        if (i==droite)return droite;
        else if (i==haut) return haut;
        else return gauche;
    }
    else if (haut==0)
    {
        i=min (droite,bas);
        i=min (i,gauche);
        if (i==droite)return droite;
        else if (i==bas) return bas;
        else return gauche;
    }
    else if (droite==0)
    {
        i= min (bas,haut);
        i=min (bas,gauche);
        if (i==bas)return bas;
        else if (i==haut) return haut;
        else return gauche;
    }
    else
    {
        i=min(droite,haut);
        j=min(bas,gauche);
        i=min (i, j);
        if (i==j)
        {
            if (j==bas)return bas;
            else return gauche;
        }
        else
        {
            if (i==droite) return droite;
            else return haut;
        }
    }
    return 0;
}

char deplacementIA (int x, int y, int z, int t, char tab [TAILLE_MAX][TAILLE_MAX])
{
    afficherTab2D(tab);
    getchar();
    char tamp [TAILLE_MAX], droite=0, gauche=0, haut=0, bas=0;
    getColonne(y,tab,tamp);
    int i=1,j=1;
    if (y>t) j=-1;
    else if (y==t) j=0;
    if (x>z)i=-1;
    else if (x==t) i=0;
    tab[x][y]=8;

    if((j==0)&&(i==0))
    {
        tab[x][y]=3;
        return 1;
    }
    else if ((j!=0)&&(deplacerCase(y+j,tab[x])!=0))
    {
        tunnel (x,y,tab,(j+4)%4);
        droite=deplacementIA (x,y+j,z,t,tab);
        reinitTunnel(x,y,tab);
        if (droite==1)
        {
            tab[x][y]=2;
            return 2;
        }

        if (deplacerCase(x+i,tamp)!=0)
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if (deplacerCase(x-i,tamp)!=0)
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if ((deplacerCase(y-j,tab[x])!=0)&&(testRetour(x,tamp)!=0))
        {
            tunnel (x,y,tab,(-j+4)%4);
            gauche=deplacementIA(x,y-j,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        switch (quatresChemins(droite,bas,haut,gauche))
        {
            case 1: tab[x][y]=2;
                    return 1+droite;
                    break;
            case 2: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 3: tab[x][y]=2;
                    return 1+haut;
                    break;
            case 4: tab[x][y]=2;
                    return 1+gauche;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    else if (j==0)
    {
        if (deplacerCase(x+i,tamp)!=0)
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
            if (bas==1)
            {
                tab[x][y]=2;
                return 2;
            }
        }

        if (deplacerCase(y+1,tab[x])!=0)
        {
            tunnel (x,y,tab,1);
            droite=deplacementIA (x,y+1,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if (deplacerCase(x-i,tamp)!=0)
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if ((deplacerCase(y-1,tab[x])!=0)&&(testRetour(x,tamp)!=0))
        {
            tunnel (x,y,tab,3);
            gauche=deplacementIA(x,y-1,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        switch (quatresChemins(bas,droite,haut,gauche))
        {
            case 1: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 2: tab[x][y]=2;
                    return 1+droite;
                    break;
            case 3: tab[x][y]=2;
                    return 1+haut;
                    break;
            case 4: tab[x][y]=2;
                    return 1+gauche;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    else
    {
        if (deplacerCase(x+i,tamp)!=0)
        {
            tunnel (x,y,tab,(i+3)%4);
            bas=deplacementIA(x+i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if (deplacerCase(y-j,tab[x])!=0)
        {
            tunnel (x,y,tab,(-j+4)%4);
            gauche=deplacementIA(x,y-j,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        if ((deplacerCase(x-i,tamp)!=0)&&(testRetour(y,tab[x])!=0))
        {
            tunnel (x,y,tab,(-i+3)%4);
            haut=deplacementIA(x-i,y,z,t,tab);
            reinitTunnel(x,y,tab);
        }

        switch (quatresChemins(bas,gauche,haut,0))
        {
            case 1: tab[x][y]=2;
                    return 1+bas;
                    break;
            case 2: tab[x][y]=2;
                    return 1+gauche;
                    break;
            case 3: tab[x][y]=2;
                    return 1+haut;
                    break;
            default: tab[x][y]=0;
                    return 0;
                    break;
        }
    }
    return 0;
}

int main()
{
    char tab [TAILLE_MAX][TAILLE_MAX], ligne [TAILLE_MAX+2];
    FILE* fTerr=fopen("data/Terrains.txt", "r");
    int i,j;
    if (fTerr!=NULL)
    {
        for (i=0; i<4;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
        }
        for (i=0;i<TAILLE_MAX;i++)
        {
            fgets(ligne,TAILLE_MAX+2,fTerr);
            for (j=0;j<TAILLE_MAX;j++)
            {
                tab[i][j]=ligne[j]-'0';
            }
        }
        fclose (fTerr);
        tab[3][3]=3;
        tab[17][17]=3;
        afficherTab2D(tab);
        printf("\n%d\n", deplacementIA(3,3,17,17,tab));
        afficherTab2D(tab);

    }
    else printf ("\nImpossible d'ouvrir le fichier Terrains.txt\n");

    return 0;
}

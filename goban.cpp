

#include "goban.h"
#include <iostream>
#include <fstream>

using namespace std;

void goban::jouer(int x,int y)
{
    // On sauvegarde notre plateau dans un premier temps
    vector<vector<int>> save;
    save = plateau;

    if (plateau[x][y] != -1) // Si la case n'est pas vide
    {
        int x2,y2;
        cout<<"Case déjà occupée,rejouez"<<endl;
        cout<<"nouvelle valeur de x:"<<endl;
        cin>>x2;
        cout<<endl<<"nouvelle valeur de y:"<<endl;
        cin>>y2;
        jouer(x2,y2);
    }

    else{

        plateau[x][y] = joueur;
        for (int i=0;i<taille;i++)
        {
            for(int j=0;j<taille;j++)
            {
                if (!detecterLiberte(i,j))
                {
                        supprimerGroupe(i,j);
                }
            }
        }
        if (detecterSuicide(x,y))
        {
            plateau = save;
            int x2,y2;
            cout<<"Suicide interdit,rejouez"<<endl;
            cout<<"nouvelle valeur de x:"<<endl;
            cin>>x2;
            cout<<endl<<"nouvelle valeur de y:"<<endl;
            cin>>y2;
            jouer(x2,y2);
        }
        }
}

void goban::ecriture()
{
    ofstream fichier("historique.txt",ios::out | ios::app);
    if (fichier)
    {
        for (int i=0;i<taille;i++)
    }
}

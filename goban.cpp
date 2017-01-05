#include "goban.h"
#include <iostream>
#include <fstream>

using namespace std;

void goban::jouer(int x,int y)
{
	// On sauvegarde notre plateau dans un premier temps
	vector<vector<int>> save;
	sauvegarder(&save);

	if ((x>=taille)||(y>=taille)||(x<0)||(y<0)){
		int x2,y2;
		cout<<"Hors plateau. Rejouez."<<endl;
	}
	else if (plateau[x][y] != -1) // Si la case n'est pas vide
	{
		int x2,y2;
		cout<<"Case déjà occupée,rejouez"<<endl;
	}
	else{
		plateau[x][y] = joueur;
		for (int i=0;i<taille;i++)
		{
			for(int j=0;j<taille;j++)
			{
				if ((plateau[i][j]!=-1)&&(!detecterLiberte(i,j)))
				{
						supprimerGroupe(i,j);
				}
			}
		}
		if (detecterSuicide(x,y))
		{

			charger(save);
			int x2,y2;
			cout<<"Suicide interdit,rejouez"<<endl;
		} else {
			joueur +=1;
			joueur = joueur%2;
		}

	}
}

void goban::ecriture()
{
    //on va écrire la configuratoin actuelle du plateau dans un fichier .txt de sauvegarde
	ofstream fichier("historique.txt",ios::out | ios::app); // On ouvre le fichier en écriture sans en efacer le contenu
	if (fichier)
	{
		for (int i=0;i<taille;i++)
		{
			for(int j=0;j<taille;j++)
			{
				fichier<<plateau[i][j]<<"\t";
			}
		}
	}
}

void goban::afficher() {
    // On affiche le plateau dans la table de commande
	for(int i = 0; i < plateau.size(); i++) {
		for(int j = 0; j < plateau[i].size(); j++) {
			std::cout << plateau[i][j] << " | ";
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "C'est au joueur " << ((joueur) ? "blanc" : "noir") << " de jouer." << std::endl << std::endl << std::endl;
}

goban::goban( int _taille) {

	taille = _taille;

	joueur =0;

	//Scores à 0
	capture[0]=0;
	capture[1]=0;

	// Initialisation du plateau
	for( int i=0; i<taille; i++) {
		vector<int> temp;
		plateau.push_back(temp);
		for ( int u=0; u<taille; u++) {
			plateau[i].push_back(-1); //Toutes les cases sont vides
		}
	}
}

bool goban::detecterLiberte( int x, int y ) {
	int couleur = plateau[x][y];
	bool liberte = false;
	Int2 i;
	i.i[0] = x;
	i.i[1] = y;
	checked.push_back(i);
	if ( x > 0) {
		if ( plateau[x-1][y] == -1 ) {
			liberte = true;
		}
		else if ( plateau[x-1][y] == couleur && isNotChecked(x-1,y)) {
			liberte = liberte||detecterLiberte(x-1, y);
		}
	}
	if ( y > 0) {
		if ( plateau[x][y-1] == -1 ) {
			liberte = true;
		}
		else if ( plateau[x][y-1] == couleur && isNotChecked(x,y-1)) {
			liberte = liberte||detecterLiberte(x, y-1);
		}
	}
	if ( x < taille-1) {
		if ( plateau[x+1][y] == -1 ) {
			liberte = true;
		}
		else if ( plateau[x+1][y] == couleur && isNotChecked(x+1,y)) {
			liberte = liberte||detecterLiberte(x+1, y);
		}
	}
	if ( y < taille-1) {
		if ( plateau[x][y+1] == -1 ) {
			liberte = true;
		}
		else if ( plateau[x][y+1] == couleur && isNotChecked(x,y+1)) {
			liberte = liberte||detecterLiberte(x, y+1);
		}
	}

	return liberte;

}

bool goban::isNotChecked(int x, int y) {
    // On vérifie que l'élément ed coordonées (x,y) n'a pas déjà été vérifié
	bool retour = true;
	for ( int i=0; i<checked.size(); i++) {
		if ( checked[i].i[0] == x && checked[i].i[1] == y) {
			retour = false;
		}
	}
	return retour;

}

bool goban::detecterSuicide( int x, int y ) {
    // On retourne true si la case est vide, false sinon
	if ( plateau[x][y] == -1)
		return true;
	else
		return false;
}

bool goban::lecture()
{
     // On retourne true si on est revenu à une configuration précédente false sinon
	bool egalite = true;
	int value;
	ifstream fichier("historique.txt",ios::in); // On ouvre en lecture le fichier texte où l'on a stocké les versions précédentes
	if (fichier)
	{
	    // On va vérifier pour chaque case si cela correspond à la configuration actuelle
		for (int i=0;i<taille;i++)
		{
			for (int j=0;j<taille;j++)
			{
				fichier>>value;
				egalite = (egalite && (value==plateau[i][j]));
			}
		}
	}
	return egalite;
}

void goban::sauvegarder(vector<vector<int>> *save)
{
	save->clear();// On s'assure que le plateau qui sert à sauvegarder est vide
	for( int i=0; i<taille; i++)
	{
	vector<int> temp;
	save->push_back(temp);
	//On va parcourir le tableau de sauvegarde par lignes qu'on va remplir avec les valeurs voulues
	for ( int u=0; u<taille; u++) {
		save->at(i).push_back(plateau[i][u]);
		}
	}
}

void goban::charger(vector<vector<int>> save)
{
	plateau.clear(); //On reinitialise notre plateau
	for( int i=0; i<taille; i++){
		vector<int> temp;
		plateau.push_back(temp);
		//On va parcourir le tableau à modifier par lignes qu'on va remplir avec les valeurs voulues
		for ( int u=0; u<taille; u++) {
			plateau[i].push_back(save[i][u]);
		}
	}
}

void goban::supprimerGroupe( int x, int y) {
	int couleur = plateau[x][y]; //On note le joueur à qui appartient le pion à supprimer
	plateau[x][y] = -1;
	if ( couleur != -1 ) { //On vérifie que cela correspond à un joueur et pas à une case vide
            // Puis on supprime tous les pions de même couleur adjacents qui sont donc dans le même groupe
            // On vérifie si on est ou non sur les bords
		if ( x > 0) {
			if ( plateau[x-1][y] == couleur) {
				supprimerGroupe(x-1, y);
			}
		}
		if ( y > 0) {
			if ( plateau[x][y-1] == couleur) {
				supprimerGroupe(x, y-1);
			}
		}
		if ( x < taille-1) {
			if ( plateau[x+1][y] == couleur) {
				supprimerGroupe(x+1, y);
			}
		}
		if ( y < taille-1) {
			if ( plateau[x][y+1] == couleur ) {
				supprimerGroupe(x, y+1);
			}
		}
	}
}

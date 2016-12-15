
#include <vector>
#include <iostream>

struct Int2 {
	int i[2];
};

class goban{

private:

	int taille; //taille du plateau

	std::vector<std::vector< int > > plateau; // vide -1, noir 0, blanc 1

	int joueur; // noir 0, blanc 1

	int capture[2]; // capture[0] capturé par les noirs, capturé

	std::vector<Int2> checked;

public:

	//setters
	void setTaille (int t){taille = t;}

	void setJoueur (int j)
	{ switch(j){
		case 0:
			joueur= 0;
			break;
		case 1:
			joueur = 1;
			break;
		default:
			std::cout<<"Valeur impossible. Indiquez joueur 0 ou 1"<<std::endl;
			}
	}

	//getters
	int getTaille(){return taille;}
	int getJoueur(){return joueur;}
	std::vector<std::vector< int > > getPlateau(){return plateau;}
	std::vector<Int2> getChecked() { return checked; }
	int getCase(int x, int y){ return plateau[x][y];}
	int getcapture1(){return capture[0];}
	int getcapture2(){return capture[1];}


	//méthodes
	bool detecterLiberte( int x, int y); // true si + de 1 degré, false si 0 degré

	bool detecterSuicide( int x, int y ); // Regarde le tableau et renvoie true si il y a un pion de la bonne couleur en x et y

	void supprimerGroupe( int x, int y ); // supprime le groupe qui a un pion en x et ypublic :

	bool isNotChecked(int x, int y);

	goban( int _taille );

	void jouer( int x, int y); // Sauvegarde du tableau, on fait le mouvement sur le tableau plateau, les vérifs, si problème, on recharge la sauvegarde et on met un message d'erreur

	void afficher ();

	void ecriture();

	bool lecture();

	void sauvegarder(std::vector<std::vector<int>> save);

	void charger(std::vector<std::vector<int>> save);

};

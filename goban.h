
#include <vector>

class goban{

private:

    int taille; //taille du plateau

    std::vector<std::vector< int > > plateau; // vide -1, noir 0, blanc 1

    int joueur; // noir 0, blanc 1

    int[] capture[2]; // capture[0] captur� par les noirs, captu�

    std::vector< int[2] > checked;

    bool detecterLiberte( int x, int y,); // true si + de 1 degr�, false si 0 degr�

    bool detecterSuicide( int x, int y ); // Regarde le tableau et renvoie true si il y a     un pion de la bonne couleur en x et y

    void supprimerGroupe( int x, int y ); // supprime le groupe qui a un pion en x et ypublic :

    bool isNotChecked(int x, int y);

    goban( int _taille );

    void jouer( int x, int y); // Sauvegarde du tableau, on fait le mouvement sur le tableau plateau, les v�rifs, si probl�me, on recharge la sauvegarde et on met un message d'erreur

    void afficher ();

    };

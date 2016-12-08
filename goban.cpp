

#include "goban.h"

using namespace std;

void goban::jouer(int x,int y)
{
    vector<vector<int>> save;
    save = plateau;

}

goban::goban( int _taille) {
  taille = _taille;
  joueur =0;
  capture[0]=0;
  capture[1]=0;

  // Initialisation du plateau
  for( int i=0; i<taille; i++) {
    vector<int> temp;
    plateau.push_back(temp);
    for ( int u=0; u<taille; u++) {
      plateau[i].push_back(-1);
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
    else if ( plateau[x-1][y] == couleur and isNotChecked(x-1,y)) {
      liberte = liberte||detecterLiberte(x-1, y);
    }
  }
  if ( y > 0) {
    if ( plateau[x][y-1] == -1 ) {
      liberte = true;
    }
    else if ( plateau[x][y-1] == couleur and isNotChecked(x,y-1)) {
      liberte = liberte||detecterLiberte(x, y-1);
    }
  }
  if ( x < taille-1) {
    if ( plateau[x+1][y] == -1 ) {
      liberte = true;
    }
    else if ( plateau[x+1][y] == couleur and isNotChecked(x+1,y)) {
      liberte = liberte||detecterLiberte(x+1, y);
    }
  }
  if ( y < taille-1) {
    if ( plateau[x][y+1] == -1 ) {
      liberte = true;
    }
    else if ( plateau[x][y+1] == couleur and isNotChecked(x,y+1)) {
      liberte = liberte||detecterLiberte(x, y+1);
    }
  }

  return liberte;

}

bool goban::isNotChecked(int x, int y) {
  bool retour = true;
  for ( int i=0; i<checked.size(); i++) {
    if ( checked[i].i[0] == x and checked[i].i[1] == y) {
      retour = false;
    }
  }
  return retour;

}

bool goban::detecterSuicide( int x, int y ) {
  if ( plateau[x][y] == -1)
    return true;
  else
    return false;
}

void goban::afficher() {
    for(int i = 0; i < plateau.size(); i++) {
        for(int j = 0; j < plateau[i].size(); j++) {
            std::cout << plateau[i][j] << " | ";
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << "C'est au joueur " << ((joueur) ? "blanc" : "noir") << " de jouer." << std::endl << std::endl << std::endl;
}



#include "goban.h"

using namespace std;

void goban::jouer(int x,int y)
{
    vector<vector<int>> save;
    save = plateau;

}

bool goban::detecterLiberte( int x, int y ) {
  int couleur = plateau[x][y];
  bool liberte = false;
  checked.push_back({x,y});
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
    if ( checked[i][0] == x and checked[i][1] == y) {
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

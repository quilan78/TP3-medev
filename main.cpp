#include "goban.h"

using namespace std;
int main() {
	goban *myGoban = new goban(10);
	bool go = true;
	int x,y;
	while ( go ) {
		myGoban->afficher();
		cout<<"nouvelle valeur de x:"<<endl;
		cin>>x;
		cout<<endl<<"nouvelle valeur de y:"<<endl;
		cin>>y;
		if ( x == -1 && y == -1 ) {
			go = false;
		}else {
			myGoban->jouer(x,y);
		}
	}
	return 0;
}


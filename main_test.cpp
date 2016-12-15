#include "goban.h"
#include <gtest>
int main() {
	goban *myGoban = new goban(10);
	myGoban->afficher();
	myGoban->jouer(5,5);
	myGoban->afficher();
	return 0;
}


TEST(ObjectTest, TestInitialisation) {
	goban *myGoban = new goban(10);
	EXPECT_EQ(myGoban->getTaille(), 10);
	EXPECT_EQ(myGoban->getPlayer(), 0);
	EXPECT_EQ(myGoban->getCapture()[0], 0);
	EXPECT_EQ(myGoban->getCapture()[1], 0);

	for( int i=0; i<myGoban->getTaille(); i++) {
		vector<int> temp;
		plateau.push_back(temp);
		for ( int u=0; u<taille; u++) {
			plateau[i].push_back(-1);
		}
	}
}



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
    for ( int u=0; u<taille; u++) {
	  	EXPECT_EQ(myGoban->getPlateau()[i][j], -1);
    }
  }
}


TEST(ObjectTestLiberte, TestPositions) {
  goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[0][5] = 0;
	EXPECT_EQ(myGoban->detecterLiberte(5,5), true);
	myGoban->getPlateau()[0][0] = 0;
	EXPECT_EQ(myGoban->detecterLiberte(0,0), true);
	myGoban->getPlateau()[10][10] = 0;
	EXPECT_EQ(myGoban->detecterLiberte(10,10), true);
}

TEST(ObjectTestLiberte, TestBloque) {
  goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[4][5] = 1;
	myGoban->getPlateau()[5][4] = 1;
	myGoban->getPlateau()[5][6] = 1;
	myGoban->getPlateau()[6][5] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(5,5), false);
	myGoban->getPlateau()[0][0] = 0;
	myGoban->getPlateau()[1][0] = 1;
	myGoban->getPlateau()[0][1] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(0,0), false);
	myGoban->getPlateau()[10][10] = 0;
	myGoban->getPlateau()[9][10] = 1;
	myGoban->getPlateau()[10][9] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(10,10), false);
}

TEST(ObjectTestLiberte, TestGroupeNonBloque) {
  goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[4][5] = 1;
	myGoban->getPlateau()[5][4] = 1;
	myGoban->getPlateau()[5][6] = 1;
	myGoban->getPlateau()[6][5] = 0;
	EXPECT_EQ(myGoban->detecterLiberte(5,5), true);
	myGoban->getPlateau()[0][0] = 0;
	myGoban->getPlateau()[1][0] = 0;
	myGoban->getPlateau()[0][1] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(0,0), true);
	myGoban->getPlateau()[10][10] = 0;
	myGoban->getPlateau()[9][10] = 1;
	myGoban->getPlateau()[10][9] = 0;
	EXPECT_EQ(myGoban->detecterLiberte(10,10), true);
}

TEST(ObjectTestLiberte, TestGroupeBloque) {
  goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[4][5] = 1;
	myGoban->getPlateau()[5][4] = 1;
	myGoban->getPlateau()[5][6] = 1;
	myGoban->getPlateau()[6][5] = 0;
	myGoban->getPlateau()[6][4] = 1;
	myGoban->getPlateau()[6][6] = 1;
	myGoban->getPlateau()[7][5] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(5,5), false);
	myGoban->getPlateau()[0][0] = 0;
	myGoban->getPlateau()[1][0] = 0;
	myGoban->getPlateau()[0][1] = 1;
	myGoban->getPlateau()[1][1] = 1;
	myGoban->getPlateau()[2][0] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(0,0), false);
	myGoban->getPlateau()[10][10] = 0;
	myGoban->getPlateau()[9][10] = 1;
	myGoban->getPlateau()[10][9] = 0;
	myGoban->getPlateau()[9][9] = 1;
	myGoban->getPlateau()[10][8] = 1;
	EXPECT_EQ(myGoban->detecterLiberte(10,10), false);
}

TEST(ObjectTestSuicide, TestSuicide) {
  goban *myGoban = new goban(10);
	EXPECT_EQ(myGoban->detecterSuicide(5,5), true);
	myGoban->getPlateau()[9][9] = 1;
	EXPECT_EQ(myGoban->detecterSuicide(9,9), false);
}

TEST(ObjetTestSupprimer, testSupprimerRien) {
	goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][6] = 0;
	myGoban->supprimerGroupe(5,5);
	EXPECT_EQ(myGoban->getPlateau()[5][5], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][6], 0);
}

TEST(ObjetTestSupprimer, testSupprimer1) {
	goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[5][6] = 1;
	myGoban->supprimerGroupe(5,5);
	EXPECT_EQ(myGoban->getPlateau()[5][5], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][6], 1);
}

TEST(ObjetTestSupprimer, testSupprimerGroupe) {
	goban *myGoban = new goban(10);
	myGoban->getPlateau()[5][5] = 0;
	myGoban->getPlateau()[5][6] = 0;
	myGoban->getPlateau()[5][7] = 0;
	myGoban->getPlateau()[6][6] = 0;
	myGoban->getPlateau()[5][4] = 1;
	myGoban->supprimerGroupe(5,5);
	EXPECT_EQ(myGoban->getPlateau()[5][5], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][6], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][7], -1);
	EXPECT_EQ(myGoban->getPlateau()[6][6], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][4], 1);
}

TEST(ObjetTestChecked, testChecked) {
	goban *myGoban = new goban(10);
	Int2 i;
	i.i[0] = 5;
	i.i[1] = 5;
	myGoban->getChecked().push_back(i);
	EXPECT_EQ(myGoban->isNotChecked()[5][5], -1);
	EXPECT_EQ(myGoban->isNotChecked()[5][6], -1);
}

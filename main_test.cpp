//#define HAVE_STRUCT_TIMESPEC 1
//#include "pthread.h"
#include "goban.h"
#include "gtest/gtest.h"
using namespace std;



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



TEST(ObjectTestLiberte, TestPositions) {
  goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(0,0,0);
	EXPECT_EQ(myGoban->detecterLiberte(5,5), true);
	myGoban->setCase(0,0,0);
	EXPECT_EQ(myGoban->detecterLiberte(0,0), true);
	myGoban->setCase(9,9,0);
	EXPECT_EQ(myGoban->detecterLiberte(9,9), true);
}

TEST(ObjectTestLiberte, TestBloque) {
  goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(4,5,1);
	myGoban->setCase(5,4,1);
	myGoban->setCase(5,6,1);
	myGoban->setCase(6,5,1);
	EXPECT_EQ(myGoban->detecterLiberte(5,5), false);
	myGoban->setCase(0,0,0);
	myGoban->setCase(1,0,1);
	myGoban->setCase(0,1,1);
	EXPECT_EQ(myGoban->detecterLiberte(0,0), false);
	myGoban->setCase(9,9,0);
	myGoban->setCase(8,9,1);
	myGoban->setCase(9,8,1);
	EXPECT_EQ(myGoban->detecterLiberte(9,9), false);
}

TEST(ObjectTestLiberte, TestGroupeNonBloque) {
  goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(4,5,1);
	myGoban->setCase(5,4,1);
	myGoban->setCase(5,6,1);
	myGoban->setCase(6,5,0);
	EXPECT_EQ(myGoban->detecterLiberte(5,5), true);
	myGoban->setCase(0,0,0);
	myGoban->setCase(1,0,0);
	myGoban->setCase(0,1,1);
	EXPECT_EQ(myGoban->detecterLiberte(0,0), true);
	myGoban->setCase(9,9,0);
	myGoban->setCase(8,9,1);
	myGoban->setCase(9,8,0);
	EXPECT_EQ(myGoban->detecterLiberte(9,9), true);
}

TEST(ObjectTestLiberte, TestGroupeBloque) {
  goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(4,5,1);
	myGoban->setCase(5,4,1);
	myGoban->setCase(5,6,1);
	myGoban->setCase(6,5,0);
	myGoban->setCase(6,4,1);
	myGoban->setCase(6,6,1);
	myGoban->setCase(7,5,1);
	EXPECT_EQ(myGoban->detecterLiberte(5,5), false);
	myGoban->setCase(0,0,0);
	myGoban->setCase(1,0,0);
	myGoban->setCase(0,1,1);
	myGoban->setCase(1,1,1);
	myGoban->setCase(2,0,1);
	EXPECT_EQ(myGoban->detecterLiberte(0,0), false);
	myGoban->setCase(9,9,0);
	myGoban->setCase(8,9,1);
	myGoban->setCase(9,8,0);
	myGoban->setCase(8,8,1);
	myGoban->setCase(9,7,1);
	EXPECT_EQ(myGoban->detecterLiberte(9,9), false);
}

TEST(ObjectTestSuicide, TestSuicide) {
  goban *myGoban = new goban(10);
	EXPECT_EQ(myGoban->detecterSuicide(5,5), true);
	myGoban->setCase(9,9,1);
	EXPECT_EQ(myGoban->detecterSuicide(9,9), false);
}

TEST(ObjetTestSupprimer, testSupprimerRien) {
	goban *myGoban = new goban(10);
	myGoban->setCase(5,6,0);
	myGoban->supprimerGroupe(5,5);
	EXPECT_EQ(myGoban->getPlateau()[5][5], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][6], 0);
}

TEST(ObjetTestSupprimer, testSupprimer1) {
	goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(5,6,1);
	myGoban->supprimerGroupe(5,5);
	EXPECT_EQ(myGoban->getPlateau()[5][5], -1);
	EXPECT_EQ(myGoban->getPlateau()[5][6], 1);
}

TEST(ObjetTestSupprimer, testSupprimerGroupe) {
	goban *myGoban = new goban(10);
	myGoban->setCase(5,5,0);
	myGoban->setCase(5,6,0);
	myGoban->setCase(5,7,0);
	myGoban->setCase(6,6,0);
	myGoban->setCase(5,4,1);
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
	myGoban->pushBackChecked(i);
	EXPECT_EQ(myGoban->isNotChecked(5,5), false);
	EXPECT_EQ(myGoban->isNotChecked(5,6), true);
}

TEST(ObjectTest, TestInitialisation) {
	goban *myGoban = new goban(10);
	EXPECT_EQ(myGoban->getTaille(), 10);
	EXPECT_EQ(myGoban->getJoueur(), 0);
	EXPECT_EQ(myGoban->getCapture1(), 0);
	EXPECT_EQ(myGoban->getCapture2(), 0);
    for( int i=0; i<myGoban->getTaille(); i++) {
        for ( int u=0; u<myGoban->getTaille(); u++) {
            EXPECT_EQ(myGoban->getPlateau()[i][u], -1);
        }
    }
}


TEST (TestCreationFichier, TestEcritureInit){
    goban *myGoban = new goban(10);
    myGoban->ecriture();
    EXPECT_EQ(myGoban->lecture(),true);
}

TEST (TestJouer,JoueursPosentPion){
    goban *myGoban = new goban(10);
    myGoban->setJoueur(0);
    myGoban->jouer(2,3);
    EXPECT_EQ(myGoban->getCase(2,3),0);
    EXPECT_EQ(myGoban->getJoueur(),1);
    myGoban->jouer(5,8);
    EXPECT_EQ(myGoban->getCase(5,8),1);
    EXPECT_EQ(myGoban->getJoueur(),0);
}

TEST (TestJouer,CaseOccupee){
    goban *myGoban = new goban(10);
    myGoban->setJoueur(0);
    myGoban->jouer(2,3);
    myGoban->jouer(2,3);
    EXPECT_EQ(myGoban->getCase(2,3),0);
    EXPECT_EQ(myGoban->getJoueur(),1);
}

TEST (TestJouer,SupprimerGroupe){
    goban *myGoban = new goban(10);
    myGoban->setJoueur(1);
    myGoban->jouer(1,1);
    myGoban->setJoueur(0);
    myGoban->jouer(1,0);
    myGoban->setJoueur(0);
    myGoban->jouer(2,1);
    myGoban->setJoueur(0);
    myGoban->jouer(1,2);
    myGoban->setJoueur(0);
    myGoban->jouer(0,1);
    EXPECT_EQ(myGoban->getCase(1,1),-1);
}

TEST (TestJouer,HorsPlateau){
    goban *myGoban = new goban(10);
    myGoban->jouer(11,0);
    for (int i=0;i<myGoban->getTaille();i++){
        for (int j=0;j<myGoban->getTaille();j++)
        {
			EXPECT_EQ(myGoban->getCase(i,j),-1);
        }
    }
    EXPECT_EQ(myGoban->getJoueur(),0);
}

TEST (TestJouer,TestSuicide){
    goban *myGoban = new goban(10);
    myGoban->jouer(1,0);
    myGoban->setJoueur(0);
    myGoban->jouer(2,1);
    myGoban->setJoueur(0);
    myGoban->jouer(1,2);
    myGoban->setJoueur(0);
    myGoban->jouer(0,1);
    myGoban->jouer(1,1);
    EXPECT_EQ(myGoban->getCase(1,1),-1);
    EXPECT_EQ(myGoban->getJoueur(),1);
}

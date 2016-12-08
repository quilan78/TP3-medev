#include "goban.h"

int main() {
    goban *myGoban = new goban(10);
    myGoban->afficher();
    myGoban->jouer(5,5);
    myGoban->afficher();
    return 0;
}

#include <iostream>
#include "Controller/Controller.h"

int main() {
    Othello::Controller othello;
    othello.SetUpGame();
    othello.PlayGame();
    return 0;
}

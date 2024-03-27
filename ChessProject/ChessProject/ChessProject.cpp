#include <iostream>
#include "Chess.h"


int main()
{
    Chess game = Chess();
    game.runChess();
    game.~Chess(); // not needed

    std::cout << "Bye Bye";
}


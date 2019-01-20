#include <iostream>
#include <vector>
#include <exception>
#include "Game.hh"

using namespace std;

int main ()
{

    Game game(sf::VideoMode(800, 600), "My window");
    game.beginGame();
    return 0;
}

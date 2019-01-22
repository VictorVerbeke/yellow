#include <iostream>
#include <vector>
#include <exception>
#include <ctime>
#include "Game.hh"

using namespace std;

int main ()
{
    std::srand(std::time(nullptr));
    Game game(sf::VideoMode(800, 600), "My window");
    game.beginGame();
    return 0;
}

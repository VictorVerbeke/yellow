#include <iostream>
#include <vector>
#include <exception>
#include <ctime>
#include "Game.hh"

using namespace std;

int main ()
{
    std::srand(std::time(nullptr));
    Textures* a = new Textures();
    (*a).generateTextures();
    Game game(sf::VideoMode(800, 600), "My window");
    game.beginGame();
    return 0;
}

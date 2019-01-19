#include <iostream>
#include <vector>
#include <exception>
#include "Game.hh"

#define SPRITE_SPEED 2

using namespace std;

int main ()
{
    Game game(sf::VideoMode(800, 600), "My window");
    try {
        game.beginGame();
    } catch (exception &ex) {
        cout << "Erreur : " << ex.what() << endl;
    }
    return 0;
}

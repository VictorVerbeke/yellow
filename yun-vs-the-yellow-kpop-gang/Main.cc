#include <iostream>
//#include <exception> // Lui, il sert plus à rien, mais qu'est-ce qu'il a servi
#include <ctime>       // durant le debuggage. Je le mets à titre posthume.
#include "Game.hh"

using namespace std;

int main ()
{
    std::srand(std::time(NULL)); // On définit un seed en fonction de l'heure.
    Textures a;             // On initialise un objet Textures, qui servira
    a.generateTextures();   // durant toute la partie à contenir les textures.
    Game game(sf::VideoMode(800, 600), "YUN VS The Yellow K-pop Gang!!");
    game.beginGame();   // Fonction principale contenant toutes les instructions
    return 0;           // pour gérer correctement le jeu. Y'aura de la lecture
}                       // dans Game.cc, je préviens tout de suite :P

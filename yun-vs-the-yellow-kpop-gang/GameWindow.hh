#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include <string>
#include <cmath>
#include "Player.hh"
#include "Pellet.hh"
#include "Enemy.hh"
#include "Boss.hh"
#include "PowerUp.hh"

using namespace std;

class GameWindow: public sf::RenderWindow {
    public :
        GameWindow();
        GameWindow(sf::VideoMode mode, string name);
        ~GameWindow();

        // Methodes de déplacement
        void moveEntity(Player *object, float x, float y);
        void moveEntity(Boss *object, float x, float y);
        void moveEntity(Enemy *object, float x, float y);
        void moveEntity(PowerUp *object);
        void moveEntity(Pellet *object);

        // Methodes d'affichage
        void drawEntity(Player *object);
        void drawEntity(Boss *object);
        void drawEntity(Enemy *object);
        void drawEntity(PowerUp *object);
        void drawEntity(Pellet *object);


    private :
        // Rien LOL

};

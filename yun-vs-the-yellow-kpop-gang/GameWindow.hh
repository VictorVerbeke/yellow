#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include <string>
#include "Entity.hh"

using namespace std;

class GameWindow: public sf::RenderWindow{
    public :
        GameWindow();
        GameWindow(sf::VideoMode mode, string name);
        ~GameWindow();

        void setPosition(Entity object, float x, float y);

        void drawItem(Entity object);


    private :
        // Rien LOL

};

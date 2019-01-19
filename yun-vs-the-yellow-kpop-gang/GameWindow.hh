#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>
#include <string>

using namespace std;

class GameWindow: public sf::RenderWindow{
    public :
        GameWindow();
        GameWindow(sf::VideoMode mode, string name);
        ~GameWindow();

        template <typename T>
        void setPosition(T object, float x, float y);

        template <typename T>
        void drawItem(T object);


    private :
        // Rien LOL

};

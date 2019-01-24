#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include "Textures.hh"
#include <iostream>
#include <algorithm>

using namespace std;

class Player: public Character {
    public:
        Player();
        Player (float x, float y, float size, sf::Texture* tex);
        ~Player();
        // Overload opérateurs
        void operator-(const float &b);

        // Methodes
        Pellet fire(sf::Vector2f targetPos); // Mais par contre, j'utilise pas
        void decreaseCD();                   // la position de fire(). Ahah.
        void move(int x, int y);
        void move(){cout << "Faut pas utiliser move() sur yun, mais move(x, y) !" << endl ; };

        // Getter, Setter.
        int getInvulCD();
        void setInvulCD(int newCD);

        unsigned int getFireCD();
        void setFireCD(unsigned int newCD);

        bool getIsHurt();
        void setIsHurt(bool newBool);

    private:
        int _invulCD;
        unsigned int _fireCD;
        bool _isHurt; //Indique si il est touché, pour l'animation.
};

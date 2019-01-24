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
        void move(){cout << "Faut pas utiliser move() sur yun, mais move(x, y) !" << endl; };

        // Getter
        unsigned int getFireCD(){ return _fireCD; }
        int getInvulCD() { return _invulCD; }
        bool getIsHurt() { return _isHurt; }
        // Setter
        void setFireCD(unsigned int newCD) { _fireCD = newCD; }
        void setInvulCD(int newCD) { _invulCD = newCD; }
        void setIsHurt(bool newBool) { _isHurt = newBool; }

    private:
        int _invulCD;
        unsigned int _fireCD;
        bool _isHurt; //Indique si il est touché, pour l'animation.
};

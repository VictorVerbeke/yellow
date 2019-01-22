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
        Pellet* fire();
        void decreaseCD();

        // Attributs
        int _invulCD;
        sf::Texture _hurtTex;
        sf::Texture _hurt_f1_Tex;
        sf::Texture _stillTex;
        bool _isHurt; //Indique si il est touché, pour l'animation.

    protected:
        unsigned int _fireCD;
};

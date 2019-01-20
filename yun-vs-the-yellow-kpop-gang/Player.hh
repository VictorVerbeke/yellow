#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include <iostream>
#include <algorithm>

using namespace std;

class Player: public Character {
    public:
        Player();
        Player (float x, float y, float size, string imagePath);
        ~Player();
        // Overload opérateurs
        void operator-(const float &b);

        // Methodes
        Pellet* fire();
        void decreaseCD();

        // Attributs
        int _invulCD;

    protected:
        unsigned int _fireCD;
};

#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include <iostream>

using namespace std;

enum Pattern {null, line, wave, still};

class Enemy: public Character {
    public:
        Enemy();
        Enemy(float x, float y, float size, int hp,
              string imagePath, Pattern pattern);
        ~Enemy();

        // Methodes
        Pellet* fire(sf::Vector2f yunPos);
        void decreaseCD();

        // Attributs
        Pattern _pattern;
        float _speed;
        float _direction;
        int _directionVariation;
    protected:
        unsigned int _fireCD;
};

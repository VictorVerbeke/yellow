#pragma once
#include "Character.hh"
#include "Pellet.hh"

enum Pattern {null, line, wave, still};

class Enemy: public Character {
    public:
        Enemy();
        Enemy(float x, float y, float size, int hp,
              string imagePath, Pattern pattern);
        ~Enemy();

        // Methodes
        Pellet* fire();
        void decreaseCD();

        // Attributs
        Pattern _pattern;
        float _speed;
        float _direction;
        int _directionVariation;
    protected:
        unsigned int _fireCD;
};

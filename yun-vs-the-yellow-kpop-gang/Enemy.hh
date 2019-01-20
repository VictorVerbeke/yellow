#pragma once
#include "Character.hh"
#include "Pellet.hh"

#define FIRECD 30
enum Pattern {null = -1, line = 0, wave, still};

class Enemy: public Character {
    public:
        Enemy();
        Enemy(float x, float y, float size, int hp,
              string imagePath, Pattern pattern);
        ~Enemy();
        Pellet* fire();

        Pattern _pattern;
        float _speed;
        float _direction;
        int _directionVariation;
    protected:
        unsigned int _fireCD;
};

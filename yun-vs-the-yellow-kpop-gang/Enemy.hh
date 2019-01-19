#pragma once
#include "Character.hh"
#include "Pellet.hh"

enum Pattern {line, wave, still};

class Enemy: public Character {
    public:
        Enemy();
        Enemy(float x, float y, float size, int hp,
              string imagePath, Pattern pattern);
        ~Enemy();
        Pellet* fire();

        Pattern _pattern;

    protected:
        unsigned int _fireCD;
};

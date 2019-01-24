#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include "Textures.hh"
#include <iostream>

using namespace std;

enum Pattern {null, line, wave, still};

class Enemy: public Character {
    public:
        Enemy();
        Enemy(float x, float y, float size, int hp,
              sf::Texture* tex, Pattern pattern);
        ~Enemy();

        // Overloads
        void operator-(const float &b);

        // Methodes
        Pellet fire(sf::Vector2f targetPos);
        void decreaseCD();
        void move();

        // Getter, Setter.
        unsigned int getFireCD() {return _fireCD; }
        void setFireCD(unsigned int newCD) { _fireCD = newCD; }

    protected:
        // Attributs
        Pattern _pattern;
        float _speed;
        float _direction;
        int _directionVariation;
        unsigned int _fireCD;
};

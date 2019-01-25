#pragma once
#include "Entity.hh"
#include "Textures.hh"

#define PI 3.141592653
#define POWERUPSPEED 1.5

enum BonusType { speed, power, invul };

class PowerUp: public Entity {
    public:
        PowerUp(float x, float y, sf::Texture* tex, BonusType type, int power);
        ~PowerUp();

        void move();

        BonusType _type;
        int _power;
        float _speed;
        float _direction;
    private:
};

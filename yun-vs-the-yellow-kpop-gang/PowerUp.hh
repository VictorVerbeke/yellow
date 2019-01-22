#pragma once
#include "Entity.hh"
#include "Textures.hh"

enum BonusType { speed, strength, invul };

class PowerUp: public Entity {
    public:
        PowerUp(float x, float y, float size, sf::Texture* tex, BonusType type, int power);
        ~PowerUp();

        BonusType _type;
        int _power;
        float _speed;
        float _direction;
    private:

};

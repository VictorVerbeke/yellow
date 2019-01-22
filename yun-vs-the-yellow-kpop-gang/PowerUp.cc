#include "PowerUp.hh"
#define POWERUPSPEED 1.5

PowerUp::PowerUp(float x, float y, float size, sf::Texture* tex, BonusType type, int power)
:
    Entity(x, y, size, tex),
    _type(type),
    _power(power),
    _speed(POWERUPSPEED),
    _direction(270)//Orienté vers le bas
    {}


PowerUp::~PowerUp(){
    delete(this);
}

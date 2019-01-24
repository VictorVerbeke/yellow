#include "PowerUp.hh"
#include <cmath>

PowerUp::PowerUp(float x, float y, float size, sf::Texture* tex, BonusType type, int power)
:
    Entity(x, y, size, tex, 0, 0, size, size),
    _type(type),
    _power(power),
    _speed(POWERUPSPEED),
    _direction(270)//Orienté vers le bas
    {}


PowerUp::~PowerUp(){
}

void PowerUp::move(){
    float newX, newY;
    newX = getX() + _speed * sin(_direction * PI /180);
    newY = getY() + _speed * cos(_direction * PI /180);
    setPosition(newX, newY);
}

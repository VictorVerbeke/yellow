#include "PowerUp.hh"
#include <cmath>

PowerUp::PowerUp(float x, float y, sf::Texture* tex, BonusType type, float power)
:
    Entity(0, 0, 32, tex, 0, 0, 32, 32),
    _type(type),
    _power(power),
    _speed(1), // C'est leeent. Faut bien les attraper !
    _direction(180) // Vers la gauche
{
    this->_x = x;
    this->_y = y;
}


PowerUp::~PowerUp(){
}

void PowerUp::move(){
    // Le powerUp va constamment vers la gauche, mais j'ai copié-collé move()
    // d'une autre classe donc bon. C'est plus joli aussi, ça marche pour
    // toutes les directions si j'ai envie de modifier ça plus tard !
    float newX, newY;
    newX = getX() + _speed * cos(_direction * PI /180);
    newY = getY() + _speed * sin(_direction * PI /180);
    setPosition(newX, newY);
}

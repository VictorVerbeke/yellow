#include <iostream>
#include "Entity.hh"

using namespace std;

Entity::Entity (float x, float y, float size, sf::Texture* tex)
:
    _size(size),
    _x(x),
    _y(y)
{
    (*tex).setSmooth(true);
    _sprite.setTexture(*tex);
    _sprite.setTextureRect(sf::IntRect(_x, _y, _size, _size));
    _sprite.setPosition(_x, _y);
    _sprite.setTexture(*tex);
}

//
// void Entity::setPosition(float x, float y){
//     _x = x;
//     _y = y;
// }

#include <iostream>
#include "Entity.hh"

using namespace std;

Entity::Entity (float x, float y, float size, string imagePath)
:
    _size(size),
    _x(x),
    _y(y)
{
    int res = _texture.loadFromFile(imagePath);
    if (!res) {
        cout << "Error reading texture file (" << imagePath << ")." << endl;
        exit(1);
    }
    _texture.setSmooth(true);
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(_x, _y, _size, _size));
    _sprite.setPosition(_x, _y);
    _sprite.setTexture(_texture);
}

//
// void Entity::setPosition(float x, float y){
//     _x = x;
//     _y = y;
// }

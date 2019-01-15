#include <iostream>
#include "Entity.hh"

using namespace std;

Entity::Entity (float x, float y, float size, string imagePath)
:
    _size(size),
    _x(x),
    _y(y)
{
    int res = _texture.loadFromFile(imagePath, sf::IntRect(x, y, size, size));
    if (!res) {
        cout << "Error reading texture file (" << imagePath << ")." << endl;
        exit(1);
    }

    _texture.setSmooth(true);
    _sprite.setTexture(_texture);
}

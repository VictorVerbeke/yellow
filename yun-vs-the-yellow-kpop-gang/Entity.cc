#include <iostream>
#include "Entity.hh"

using namespace std;

Entity::Entity (float x, float y, float size, string imagePath)
:
    _x(x),
    _y(y),
    _size(size)
{
    int res = _texture.loadFromFile(imagePath, sf::IntRect(x, y, size, size));
    if (!res) {
        cout << "Error reading texture file (" << imagePath << ")." << endl;
        exit(1);
    }

    _texture.setSmooth(true);
    _sprite.setTexture(_texture);
}

#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Entity {
    public:
        Entity (float x, float y, float size, string imagePath);
        sf::Sprite _sprite;
        float _size;
        sf::Texture _texture;

    protected:
        float _x;
        float _y;
};

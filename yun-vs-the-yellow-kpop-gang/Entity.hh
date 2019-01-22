#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.hh"
using namespace std;

class Entity {
    public:
        Entity (float x, float y, float size, sf::Texture* tex);

        float _size;
        float _x;
        float _y;
        sf::Sprite _sprite;
        sf::Texture _texture;

    protected:

};

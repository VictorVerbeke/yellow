#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Entity {
    public:
        Entity (float x, float y, float size, string imagePath);

        float _size;
        float _x;
        float _y;
        sf::Sprite _sprite;
        sf::Texture _texture;


    protected:

};

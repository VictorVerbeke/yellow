#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Entity {
    public:
        Entity (float x, float y, float size, string imagePath);
        sf::Sprite _sprite;
        float _size;
        sf::Texture _texture;

        void setPosition(float x, float y);

    protected:
        float _x;
        float _y;
};

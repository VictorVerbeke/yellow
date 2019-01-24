#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.hh"
using namespace std;

class Entity {
    public:
        Entity (float x, float y, float size, sf::Texture *tex);
        ~Entity();

        // Getter, Setter.
        float getX(){ return _x; }
        float getY(){ return _y; }
        void setPosition(float x, float y);

        // Toutes les entités peuvent se déplacer. Ajout d'une méthode
        // virtuelle.
        virtual void move() = 0;

        float _size;
        float _x;
        float _y;
        sf::Sprite _sprite;

    protected:

};

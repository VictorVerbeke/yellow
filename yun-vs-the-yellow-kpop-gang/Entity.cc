#include <iostream>
#include "Entity.hh"

using namespace std;

Entity::Entity (float x, float y, float size, sf::Texture* tex,
                float hitbox_x, float hitbox_y, float hitbox_width, float hitbox_height)
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
    _hitbox = sf::RectangleShape(sf::Vector2f(hitbox_width, hitbox_height));
    _hitbox.setPosition(hitbox_x, hitbox_y);
    _hitbox.setFillColor(sf::Color(255,255,255)); // Pour voir les hitbox en debug
}

Entity::~Entity(){

}


// Methodes
void Entity::setPosition(float x, float y){
    _x = x;
    _y = y;
    _sprite.setPosition(x, y);
    _sprite.setOrigin(_sprite.getLocalBounds().width/2, _sprite.getLocalBounds().height/2);
    _hitbox.setPosition(x, y);
}

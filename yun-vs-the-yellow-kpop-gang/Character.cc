#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.hh"

using namespace std;

Character::Character (float x, float y, float size, int hp, sf::Texture* tex,
                      float hitbox_x, float hitbox_y, float hitbox_width, float hitbox_height)
:
    Entity(x, y, size, tex, hitbox_x, hitbox_y, hitbox_width, hitbox_height),
    _hp(hp)
{}

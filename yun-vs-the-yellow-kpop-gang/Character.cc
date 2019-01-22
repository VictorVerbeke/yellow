#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.hh"

using namespace std;

Character::Character (float x, float y, float size, int hp, sf::Texture* tex)
:
    Entity(x, y, size, tex),
    _hp(hp)
{}

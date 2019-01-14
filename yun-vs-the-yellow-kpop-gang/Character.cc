#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.hh"

using namespace std;

Character::Character (float x, float y, float size, string imagePath)
:
    Entity(x, y, size, imagePath)
{}

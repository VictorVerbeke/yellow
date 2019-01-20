#include <iostream>
#include <cmath>
#include "Pellet.hh"

using namespace std;

Pellet::Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage, int target)
:
    Entity(x, y, size, imagePath),
    _speed(speed),
    _direction(direction),
    _damage(damage),
    _target(target){}

Pellet::~Pellet(){
}

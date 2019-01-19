#pragma once
#include "Entity.hh"

class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage);
        ~Pellet();

        float _speed;
        float _direction;
        int _damage;
    private:

};

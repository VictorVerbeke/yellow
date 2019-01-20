#pragma once
#include "Entity.hh"

class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage, int target);
        ~Pellet();

        float _speed;
        float _direction;
        int _damage;
        int _target; //0 pour joueur, 1 pour enemy
    private:

};

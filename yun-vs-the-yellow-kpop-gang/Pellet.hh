#pragma once
#include "Entity.hh"
#include "Textures.hh"


class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage, int target);
        ~Pellet();

        void nextFrame();

        float _speed;
        float _direction;
        int _damage;
        int _target; //0 pour joueur, 1 pour enemy
        int _frameCounter;  // De 0 à 3
    private:
        int _frameNumber;   // De 0 à 7

};

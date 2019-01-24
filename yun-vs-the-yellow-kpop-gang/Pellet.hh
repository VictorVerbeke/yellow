#pragma once
#include "Entity.hh"
#include "Textures.hh"

#define PI 3.141592653

class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, sf::Texture* tex,
               float speed, float direction, int damage, int target);
        ~Pellet();

        void nextFrame();
        void move();

        float _speed;
        float _direction;
        int _damage;
        int _target; //0 pour joueur, 1 pour enemy
        int _frameCounter;  // De 0 à 3
    private:
        int _frameNumber;   // De 0 à 7

};

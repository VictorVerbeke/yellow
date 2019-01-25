#pragma once
#include "Entity.hh"
#include "Textures.hh"

#define PI 3.141592653

class Pellet : public Entity {
    public:
        Pellet(float x, float y, float size, sf::Texture* tex,
               float speed, float direction, int damage, int target);
        ~Pellet();

        // Méthodes
        void nextFrame();
        void move();

        // Getter, Setter
        int getDamage(){ return _damage; };
        int getTarget(){ return _target; };

    private:
        float _speed;
        float _direction;
        int _frameNumber;   // De 0 à 7
        int _frameCounter;  // De 0 à 3
        int _damage;
        int _target; //0 pour joueur, 1 pour enemy

};

#pragma once
#include "Entity.hh"
#include "Textures.hh"

#define PI 3.141592653 // Regardez, on utilise pi, on fait des maths !

// Trois types de powerUp : dégats, vitesse et temps d'invulnérabilité accrus.
enum BonusType { speed, power, invul };

class PowerUp: public Entity {
    public:
        // Créateur, destructeur
        PowerUp(float x, float y, sf::Texture* tex, BonusType type, float power);
        ~PowerUp();

        // Méthodes.
        void move();

        // Getter, Setter
        BonusType getType(){ return _type; }
        float getPower(){ return _power; }

    private:
        // Attributs.
        BonusType _type;
        float _power;
        float _speed;
        float _direction;
};

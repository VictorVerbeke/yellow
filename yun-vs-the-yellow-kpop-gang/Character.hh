#pragma once
#include "Entity.hh"
#include "Pellet.hh"
#include "Textures.hh"

#define PI 3.141592653

using namespace std;

class Character: public Entity {
    public:
        Character (float x, float y, float size, int hp, sf::Texture* tex,
                   float hitbox_x, float hitbox_y, float hitbox_width, float hitbox_height);
        int getHp () { return _hp; };
        void setHp (int hp) { _hp = hp; };
        void addHp (int hp) { _hp -= hp; };

        // Une fonction virtuelle, car tous les characters utilisent fire().
        virtual Pellet fire(sf::Vector2f targetPos) = 0;
        virtual void decreaseCD() = 0;

        // Les attributs statiques partagés par tous les characters.
        // Ils sont initialisés à l'initialisation de Yun, et modifiés par
        // la difficulté et les power-ups.
        static float _playerFireCD;
        static float _playerFireDamage;
        static float _playerFireSpeed;
        static float _playerMovementSpeed;
        static float _playerInvulCD;
        static float _enemyFireCD;
        static float _enemyFireDamage;
        static float _enemyFireSpeed;
        static float _enemyMovementSpeed;
        static float _enemyStandardHP;

    protected:
        int _hp;
};

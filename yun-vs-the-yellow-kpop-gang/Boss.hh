#pragma once
#include "Enemy.hh"
#include "Textures.hh"
#include "Character.hh"
#include "Player.hh"

enum Name { none, Beenzino, GirlGeneration, Jonghyun };

class Boss: public Enemy {
    public:
        // Constructeurs & Destructeurs
        Boss();
        Boss(Name name, sf::Texture* tex);
        ~Boss(); // LVL 1 CROOK

        // Overloads
        void operator-(const float &b);

        // Methodes
        void move();
        Pellet fire(sf::Vector2f targetPos) override;

        // Getter, Setter
        unsigned int getSpecialCD(){ return _specialFireCD; }
        void setSpecialCD(unsigned int newCD){ _specialFireCD = newCD; }

        // Attributs
        Name _name;
        int _phase;

    protected:
        unsigned int _specialFireCD;
};

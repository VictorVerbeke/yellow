#pragma once
#include "Enemy.hh"
#include "Textures.hh"
#define SPECIALFIRECD1 300
#define SPECIALFIRECD2 250
#define SPECIALFIRECD3 200

enum Name { none, Beenzino, GirlGeneration, Jonghyun };

class Boss: public Enemy {
    public:
        // Constructeurs & Destructeurs
        Boss();
        Boss(float x, float y, float size, int hp,
             sf::Texture* tex, Pattern pattern, Name name);
        ~Boss(); // LVL 1 CROOK

        // Methodes
        Pellet* SpecialFire(float size);
        void nextPhase();

        // Attributs
        Name _name;
        int _phase;

    protected:
        unsigned int _specialFireCD;
};

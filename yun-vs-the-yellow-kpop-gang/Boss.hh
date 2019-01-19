#pragma once
#include "Enemy.hh"
enum Name { GirlGeneration, _2NE1, Jonghyun };

class Boss: public Enemy {
    public:
        // Constructeurs & Destructeurs
        Boss(float x, float y, float size, int hp,
             string imagePath, Pattern pattern, Name name);
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
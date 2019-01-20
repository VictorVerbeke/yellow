#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include <algorithm>

using namespace std;

class Player: public Character {
    public:
        Player();
        Player (float x, float y, float size, string imagePath);
        ~Player();

        Pellet* fire();

    protected:
        unsigned int _fireCD;
};

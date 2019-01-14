#pragma once
#include "Entity.hh"

using namespace std;

class Character: public Entity {
    public:
        Character (float x, float y, float size, string imagePath);

    protected:
        int _hp;
};

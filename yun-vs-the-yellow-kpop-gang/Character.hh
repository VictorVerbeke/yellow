#pragma once
#include "Entity.hh"

using namespace std;

class Character: public Entity {
    public:
        Character (float x, float y, float size, int hp, string imagePath);
        int getHp () { return _hp; };
        void setHp (int hp) { _hp = hp; };
        void addHp (int hp) { _hp -= hp; };

    protected:
        int _hp;
};

#pragma once
#include "Entity.hh"
#include "Pellet.hh"

#define PLAYERFIRECD 15
#define PLAYERPELLETSPEED 10
#define ENEMYFIRECD 80
#define ENEMYPELLETSPEED 4
#define ENEMYMOVEMENTSPEED 2
#define ENEMYDAMAGE 5
#define INVULTEMPS 30
#define PI 3.141592653

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

#include "Enemy.hh"
#define FIRECD 30

Enemy::Enemy(float x, float y, float size, int hp,
             string imagePath, Pattern pattern)
:
    Character(x, y, size, 50, imagePath),
    _pattern(pattern),
    _fireCD(0){}

Enemy::~Enemy(){
    delete(this);
}

Pellet* Enemy::fire(){
    if (_fireCD > 0) {
        _fireCD --;
        return NULL; // Exception sur push_back(NULL) à faire
    }
    else {
        _fireCD = FIRECD;
        return NULL; // TODO Faire la création de Pellet
    }
}

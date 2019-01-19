#include "Player.hh"
#define FIRECD 30

Player::Player (float x, float y, float size, string imagePath)
:
    Character(x, y, size, 100, imagePath),
    _fireCD(0)
{}

Player::~Player(){
    delete(this);
}

Pellet* Player::fire(){
    if (_fireCD > 0) {
        _fireCD --;
        return NULL; // Exception sur push_back(NULL) à faire
    }
    else {
        _fireCD = FIRECD;
        return NULL; // TODO Faire la création de Pellet
    }
}
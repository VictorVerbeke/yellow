#include "Player.hh"
#define FIRECD 5

Player::Player ():
    Character(0, 0, 100, 100, "images/yun_test_100.png"),
    _fireCD(0){}

Player::Player (float x, float y, float size, string imagePath)
:
    Character(x, y, size, 100, imagePath),
    _fireCD(0){}


Player::~Player(){
    delete(this);
}

Pellet* Player::fire(){
    if (_fireCD == 0) {
        _fireCD = FIRECD;
        return new Pellet(this->_x, this->_y, 100, "images/yun_test_100.png",
                          8, 90, 20);
    }
    return NULL;
}

void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

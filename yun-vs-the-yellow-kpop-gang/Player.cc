#include "Player.hh"
#define FIRECD 5
#define PLAYERPELLETSPEED 30
#define PLAYERDAMAGE 50
using namespace std;

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
        Pellet* created = new Pellet(0, 0, 32, "images/angery_32.png",
                                    PLAYERPELLETSPEED, 0, PLAYERDAMAGE); //90 = down
        created->_x = this->_x;
        created->_y = this->_y;
        return created;
    }
    return NULL;
}

void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

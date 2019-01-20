#include "Player.hh"
#define FIRECD 15
#define PLAYERPELLETSPEED 10
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
}

// Overloads
void Player::operator-(const float &b) {
    this->setHp(this->getHp() - b);
}

// Methodes

Pellet* Player::fire(){
    if (_fireCD == 0) {
        _fireCD = FIRECD;
        Pellet* created = new Pellet(0, 0, 32, "images/angery_32.png",
                                    PLAYERPELLETSPEED, 0, PLAYERDAMAGE, 1); //90 = down
        created->_x = this->_x + this->_size - 20;
        created->_y = this->_y + (this->_size)/2 - 20;
        return created;
    }
    return NULL;
}

void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

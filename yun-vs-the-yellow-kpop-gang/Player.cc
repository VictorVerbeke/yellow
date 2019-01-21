#include "Player.hh"

using namespace std;

Player::Player ():
    Character(0, 0, 100, 100, "images/yun_test_100.png"),
    _invulCD(0),
    _fireCD(0)
{
    // Initialisation des attributs partagés par les characters. On suppose que
    // la difficulté de base est à "Normal".
    // Toutes ces valeurs sont exprimées en frames, soit n * 1/60 secondes.

}

Player::Player (float x, float y, float size, string imagePath)
:
    Character(x, y, size, 100, imagePath),
    _fireCD(0){}


Player::~Player(){
}

// Overloads
void Player::operator-(const float &b) {
    this->setHp(this->getHp() - b);
    this->_invulCD = _playerInvulCD;
    cout << "Yun a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl;
}

// Methodes

Pellet* Player::fire(){
    if (_fireCD == 0) {
        _fireCD = _playerFireCD;
        Pellet *created = new Pellet(0, 0, 32, "images/angery_32.png",
                            _playerFireSpeed, 0, _playerFireDamage, 1);
        created->_x = this->_x + this->_size - 20;
        created->_y = this->_y + (this->_size)/2 - 20;
        return created;
    }
    return NULL;
}

void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

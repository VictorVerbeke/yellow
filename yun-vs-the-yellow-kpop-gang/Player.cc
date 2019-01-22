#include "Player.hh"

using namespace std;

Player::Player ():
    Character(0, 0, 64, 100, "images/yun_still_64.png"),
    _invulCD(0),
    _fireCD(0)
{
    // Attribution des sprites still & hurt.
    int res;
    res = _stillTex.loadFromFile("images/yun_still_64.png");
    if (!res) {
        cout << "Error reading texture (images/yun_still_64.png)" << endl;
        exit(1);
    }
    res = _hurtTex.loadFromFile("images/yun_hurt_64.png");
    if (!res) {
        cout << "Error reading texture (images/yun_hurt_64.png)" << endl;
        exit(1);
    }
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
    this->_isHurt = true;
    this->_invulCD = _playerInvulCD;
    cout << "Yun a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl;
}

// Methodes

Pellet* Player::fire(){
    if (_fireCD == 0) {
        _fireCD = _playerFireCD;
        Pellet *created = new Pellet(0, 0, 32, "images/pellets/ally_spr_0.png",
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

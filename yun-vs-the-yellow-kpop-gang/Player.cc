#include "Player.hh"

using namespace std;

Player::Player ():
    Character(0, 0, 64, 100, Textures::_yun_still_tex),
    _invulCD(0),
    _fireCD(0)
{}

Player::Player (float x, float y, float size, sf::Texture* tex)
:
    Character(x, y, size, 100, tex),
    _fireCD(0){}


Player::~Player(){
}

// Overloads
void Player::operator-(const float &b) {
    this->setHp(this->getHp() - b);
    this->_isHurt = true;
    this->_invulCD = _playerInvulCD;
    this->_sprite.setTexture(*(Textures::_yun_hurt_f1_tex));
    cout << "Yun a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl;
}

// Methodes
Pellet Player::fire(sf::Vector2f targetPos){
    _fireCD = _playerFireCD;
    Pellet created(0, 0, 32, Textures::_allyPellet_tex0,
                   _playerFireSpeed, 0, _playerFireDamage, 1);
    created._x = this->_x + this->_size - 20;
    created._y = this->_y + (this->_size)/2 - 20;
    return created;
}

void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}
void Player::move(int x, int y){
    setPosition(x + _x, y + _y);
}
// Getter, Setter.
int Player::getInvulCD(){
    return _invulCD;
}

void Player::setInvulCD(int newCD){
    _invulCD = newCD;
}


unsigned int Player::getFireCD(){
    return _fireCD;
}

void Player::setFireCD(unsigned int newCD){
    _fireCD = newCD;
}


bool Player::getIsHurt(){
    return _isHurt;
}

void Player::setIsHurt(bool newBool){
    _isHurt = newBool;
}

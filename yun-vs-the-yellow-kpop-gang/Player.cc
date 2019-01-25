#include "Player.hh"

using namespace std;

Player::Player ():
    Character(0, 0, 64, 100, Textures::texMap[_yun_still_tex], 10, 10, 44, 44),
    _invulCD(0),
    _fireCD(0)
{}

Player::Player (float x, float y, float size, sf::Texture* tex)
:
    Character(x, y, size, 100, tex, 10, 10, 44, 44),
    _invulCD(0),
    _fireCD(0){}


Player::~Player(){
}

// Overload sur - b :
// On réduit les points de vie du joueur, on dit qu'il a mal (via _isHurt),
// on initialise son temps d'invincibilité, on met sa texture en rouge
// (mais elle sera remise en normal après, juste pour faire un flash rouge
// qui indique qu'on a pris des dégats à cette frame), et on dit dans la console
// que Yun a perdu des points de vie.
void Player::operator-(const float &b) {
    this->setHp(this->getHp() - b);
    this->_isHurt = true;
    this->_invulCD = _playerInvulCD;
    this->_sprite.setTexture(*(Textures::texMap[_yun_hurt_f1_tex]));
    cout << "Yun a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl << endl;
}

// Methodes
// Quand Yun tire, il tire tout droit. On utiilse donc PAS targetPos, mais
// il est quand même mis en argument sinon il y a conflit avec la classe mère.
// On crée un Pellet, on lui donne les caractéristiques du joueur, on la
// position et ensuite on la retourne.
Pellet Player::fire(sf::Vector2f targetPos){
    _fireCD = _playerFireCD;
    Pellet created(0, 0, 32, Textures::texMap[_allyPellet_tex0],
                   _playerFireSpeed, 0, _playerFireDamage, 1);
    created.setPosition(this->_x + this->_size - 20, this->_y + (this->_size)/2 - 20);
    return created;
}

// Ca permet juste de décrémenter le cooldown de _fireCD.
// C'est incroyable des fois, l'informatique.
void Player::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

// Cette méthode permet de bouger le personnage de (x, y).
// Elle bouge aussi la hitbox d'un certain offset.
void Player::move(int x, int y){
    setPosition(x + _x, y + _y);
    _hitbox.setPosition(_x + 10, _y + 10);
}

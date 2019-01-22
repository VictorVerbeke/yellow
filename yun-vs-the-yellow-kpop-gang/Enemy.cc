#include "Enemy.hh"
#include <math.h>

Enemy::Enemy(float x, float y, float size, int hp,
             sf::Texture* tex, Pattern pattern)
:
    Character(0, 0, size, 50, tex),
    _pattern(pattern),
    _speed(_enemyMovementSpeed),
    _direction(-90),
    _directionVariation(1),
    _fireCD(_enemyFireCD)
{
    this->_x = x;
    this->_y = y;
}

Enemy::~Enemy(){

}

// Overloads
void Enemy::operator-(const float &b) {
    this->setHp(this->getHp() - b);
}

// Methodes
Pellet* Enemy::fire(sf::Vector2f yunPos){

    if (_fireCD == 0) {
        sf::Vector2f startingPos = this->_sprite.getPosition();
        float dX = yunPos.x - startingPos.x;
        float dY = yunPos.y  - startingPos.y;
        float angle = (atan2(dY, dX) * 180 / PI);
        _fireCD = _enemyFireCD;
        Pellet *enemyPellet = new Pellet(0, 0, 32, Textures::_enemyPellet_tex0,
                                    _enemyFireSpeed, angle, _enemyFireDamage, 0);
        enemyPellet->_x = (this->_size / 2)*cos(angle/180*PI) + (this->_x);
        enemyPellet->_y = (this->_size / 2)*sin(angle/180*PI) + (this->_y);
        return enemyPellet;
    }
    return NULL;

}

void Enemy::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

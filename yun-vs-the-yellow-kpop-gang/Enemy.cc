#include "Enemy.hh"
#include <math.h>

Enemy::Enemy(float x, float y, float size, int hp,
             sf::Texture* tex, Pattern pattern)
:
    Character(0, 0, size, hp, tex, 0, 0, size, size),
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
Pellet Enemy::fire(sf::Vector2f targetPos){
    sf::Vector2f enemyPos = this->_sprite.getPosition();
    float dX = (targetPos.x) - enemyPos.x + 32;
    float dY = (targetPos.y)  - enemyPos.y + 32;
    float angle = (atan2(dY, dX) * 180 / PI);
    _fireCD = _enemyFireCD;
    Pellet enemyPellet(0, 0, 32, Textures::texMap[_enemyPellet_tex0],
                       _enemyFireSpeed, angle, _enemyFireDamage, 0);
    enemyPellet._y = (this->_size)*sin(angle/180*PI)*1.5 + (this->_y) + 16;
    enemyPellet._x = (this->_size)*cos(angle/180*PI)*1.5 + (this->_x) + 16;
    return enemyPellet;
}

void Enemy::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

void Enemy::move(){
    float newX, newY;
    switch (_pattern){
        case line:
            newX = getX() + _speed * sin(_direction * PI /180);
            newY = getY() + _speed * cos(_direction * PI /180);
            setPosition(newX, newY);
            break;

        case wave:
            newX = getX() + _speed * sin(_direction * PI /180);
            newY = getY() + _speed * cos(_direction * PI /180);
            setPosition(newX, newY);
            if (_direction >= -45) _directionVariation = -1;
            if (_direction <= -135) _directionVariation = 1;
            _direction += _directionVariation;
            break;

        case still:
            setPosition(getX(), getY());
            break;
        default:
            break;
    }
}

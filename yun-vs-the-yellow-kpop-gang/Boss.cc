#include "Boss.hh"
#include <cmath>

Boss::Boss():
    Enemy(0,0,0,100,NULL, null),
    _name(none),
    _phase(0){}

Boss::Boss(Name name, sf::Texture* tex)
:
    Enemy(600, 200, 256, 75*Character::_enemyStandardHP, tex, null),
    _name(name),
    _phase(0)
{
    switch(name){
        case Beenzino :
            _bossFireCD = _enemyFireCD * 0.75;
            _bossFireDamage = _enemyFireDamage * 5;
            _bossFireSpeed = _enemyFireSpeed * 2;
            _directionVariation = 1;
            break;
        case GirlGeneration :
            _bossFireCD = _enemyFireCD * 0.5;
            _bossFireDamage = _enemyFireDamage * 3;
            _bossFireSpeed = _enemyFireSpeed * 1.5;
            _directionVariation = 0.3;
            break;
        case Jonghyun :
            _bossFireCD = _enemyFireCD * 0.2;
            _bossFireDamage = _enemyFireDamage;
            _bossFireSpeed = _enemyFireSpeed;
            _directionVariation = 3;
            break;
        default:
            _bossFireCD = _enemyFireCD * 1000;
            _bossFireDamage = _enemyFireDamage * 0;
            _bossFireSpeed = _enemyFireSpeed * 1000;
            _directionVariation = 0;
            break;
    }
}

Boss::~Boss(){
}

// Overloads
void Boss::operator-(const float &b) {
    this->setHp(this->getHp() - b);
    cout << "Le boss a perdu " << b << " hp et est à " << this->getHp() << " hp." << endl;
}

Pellet Boss::fire(sf::Vector2f targetPos){
    cout << "Coucou. " << endl;
    sf::Vector2f bossPos = this->_sprite.getPosition();
    float dX = (targetPos.x) - bossPos.x - 64;
    float dY = (targetPos.y)  - bossPos.y - 64;
    float angle = (atan2(dY, dX) * 180 / PI);
    _fireCD = _bossFireCD;
    Pellet bossPellet(0, 0, 32, Textures::texMap[_enemyPellet_tex0],
                       _bossFireSpeed, angle, _bossFireDamage, 0);
    bossPellet._y = (this->_y)+(this->_size)/2;
    bossPellet._x = (this->_x)+(this->_size)/2;
    return bossPellet;
}
void Boss::move(){
    float newX, newY;
    if (getX() > 500) newX = getX() - 2;
    else newX = getX();
    _direction += _directionVariation;
    newY = 200 + sin(_direction * PI / 180) * 150;
    this->setPosition(newX, newY);
}

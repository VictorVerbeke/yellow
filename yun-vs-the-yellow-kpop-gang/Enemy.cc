#include "Enemy.hh"

Enemy::Enemy(float x, float y, float size, int hp,
             string imagePath, Pattern pattern)
:
    Character(x, y, size, 50, imagePath),
    _pattern(pattern),
    _speed(ENEMYMOVEMENTSPEED),
    _direction(-90),
    _directionVariation(1),
    _fireCD(0)
{}

Enemy::~Enemy(){
}

Pellet* Enemy::fire(){

    if (_fireCD > 0) {
        _fireCD --;
        return NULL; // Exception sur push_back(NULL) à faire
    }
    else {
        _fireCD = ENEMYFIRECD;
        Pellet *enemyPellet = new Pellet(0, 0, 32, "images/angery_32.png",
                                    ENEMYPELLETSPEED, 180, ENEMYDAMAGE, 0);
        enemyPellet->_x = this->_x - 5;
        enemyPellet->_y = this->_y + (this->_size)/2 - 5;
        return enemyPellet;
    }
}

void Enemy::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

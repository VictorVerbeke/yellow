#include "Enemy.hh"

Enemy::Enemy(float x, float y, float size, int hp,
             string imagePath, Pattern pattern)
:
    Character(x, y, size, 50, imagePath),
    _pattern(pattern),
    _speed(ENEMYMOVEMENTSPEED),
    _direction(-90),
    _directionVariation(1),
    _fireCD(ENEMYFIRECD)
{}

Enemy::~Enemy(){
}

Pellet* Enemy::fire(sf::Vector2f yunPos){

    if (_fireCD == 0) {
        sf::Vector2f startingPos = this->_sprite.getPosition();
        float dX = yunPos.x + 50 - startingPos.x;
        float dY = yunPos.y + 50 - startingPos.y;
        float angle = (atan2(dY, dX) * 180 / PI);
        _fireCD = ENEMYFIRECD;
        Pellet *enemyPellet = new Pellet(0, 0, 32, "images/angery_32.png",
                                    ENEMYPELLETSPEED, angle, ENEMYDAMAGE, 0);
        enemyPellet->_x = (this->_size / 2)*cos(angle/180*PI) + (this->_x);
        enemyPellet->_y = (this->_size / 2)*sin(angle/180*PI) + (this->_y);
        return enemyPellet;
    }
    return NULL;

}

void Enemy::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

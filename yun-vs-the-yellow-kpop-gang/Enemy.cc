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
    this->setPosition(x, y); // Au cas où, j'ai eu des problèmes avec ça.
}

Enemy::~Enemy(){

}

// Overloads :
// L'ennemi perd b points de vie.
void Enemy::operator-(const float &b) {
    this->setHp(this->getHp() - b);
}

// Methodes :
// fire permet de créer un Pellet qui se dirigera vers la position donnée.
// Ici, la position donnée permet de viser le joueur.
// On détermine l'angle vers le joueur, puis on crée un Pellet destiné à
// blesser le joueur, et on le position à l'emplacement de l'ennemi.
Pellet Enemy::fire(sf::Vector2f targetPos){
    sf::Vector2f enemyPos = this->_sprite.getPosition();
    float dX = (targetPos.x) - enemyPos.x + 32;
    float dY = (targetPos.y)  - enemyPos.y + 32;
    float angle = (atan2(dY, dX) * 180 / PI);

    _fireCD = _enemyFireCD; // Il ne pourra plus tirer avec (_enemyFireCD) frames.

    Pellet enemyPellet(0, 0, 32, Textures::texMap[_enemyPellet_tex0],
                       _enemyFireSpeed, angle, _enemyFireDamage, 0);
    enemyPellet.setPosition((this->_size)*cos(angle/180*PI)*1.5 + (this->_x) + 16,
                            (this->_size)*sin(angle/180*PI)*1.5 + (this->_y) + 16);

    return enemyPellet;
}

// Permet de réduire le temps d'attente pour tirer.
void Enemy::decreaseCD(){
    if (_fireCD > 0) _fireCD--;
}

// Les ennemis ont la particularité de pouvoir se déplacer selon des patterns !
// Ils peuvent aller en ligne ou en vague, still étant utilisé plutôt pour le
// debug. Selon le pattern, on choisit donc comment se déplacer.
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

            // En gros, on va à gauche, mais entre en bas à gauche et
            // en haut à gauche. Une fois atteint une direction trop basse,
            // on se redirige vers le haut, et vice-versa.
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

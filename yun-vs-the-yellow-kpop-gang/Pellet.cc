#include <iostream>
#include <cmath>
#include "Pellet.hh"

using namespace std;



Pellet::Pellet(float x, float y, float size, sf::Texture* tex,
               float speed, float direction, int damage, int target)
:
    Entity(x, y, 64, tex),
    _speed(speed),
    _direction(direction),
    _damage(damage),
    _target(target),
    _frameCounter(0),
    _frameNumber(0){
        this->_sprite.rotate(direction);
    }

Pellet::~Pellet(){
}

void Pellet::nextFrame(){
    switch(_frameNumber){
        case 0 :
            _frameNumber = 1;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex1));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex1));
            break;
        case 1 :
            _frameNumber = 2;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex2));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex2));
            break;
        case 2 :
            _frameNumber = 3;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex3));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex3));
            break;
        case 3 :
            _frameNumber = 4;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex4));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex4));
            break;
        case 4 :
            _frameNumber = 5;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex5));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex5));
            break;
        case 5 :
            _frameNumber = 6;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex6));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex6));
            break;
        case 6 :
            _frameNumber = 7;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex7));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex7));
            break;
        case 7 :
            _frameNumber = 0;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::_enemyPellet_tex0));
            else this->_sprite.setTexture(*(Textures::_allyPellet_tex0));
            break;

        default:
            break;
    }
    _frameCounter = 0;
}

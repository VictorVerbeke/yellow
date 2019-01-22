#include <iostream>
#include <cmath>
#include "Pellet.hh"

using namespace std;



Pellet::Pellet(float x, float y, float size, string imagePath,
               float speed, float direction, int damage, int target)
:
    Entity(x, y, size, imagePath),
    _speed(speed),
    _direction(direction),
    _damage(damage),
    _target(target){}

Pellet::~Pellet(){
}

void Pellet::nextFrame(){
    switch(_frameNumber){
        case 0 :
            _frameNumber = 1;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex1);
            else this->_sprite.setTexture(_ally_tex1);
            break;
        case 1 :
            _frameNumber = 2;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex2);
            else this->_sprite.setTexture(_ally_tex2);
            break;
        case 2 :
            _frameNumber = 3;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex3);
            else this->_sprite.setTexture(_ally_tex3);
            break;
        case 3 :
            _frameNumber = 4;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex4);
            else this->_sprite.setTexture(_ally_tex4);
            break;
        case 4 :
            _frameNumber = 5;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex5);
            else this->_sprite.setTexture(_ally_tex5);
            break;
        case 5 :
            _frameNumber = 6;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex6);
            else this->_sprite.setTexture(_ally_tex6);
            break;
        case 6 :
            _frameNumber = 7;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex7);
            else this->_sprite.setTexture(_ally_tex7);
            break;
        case 7 :
            _frameNumber = 0;
            if (this->_target == 0) this->_sprite.setTexture(_enemy_tex0);
            else this->_sprite.setTexture(_ally_tex0);
            break;

        default:
            break;
    }
}

void Pellet::initializeTextures(){
    int res = 0;
    res += _ally_tex0.loadFromFile("images/_ally_spr_0");
    res += _ally_tex1.loadFromFile("images/_ally_spr_1");
    res += _ally_tex2.loadFromFile("images/_ally_spr_2");
    res += _ally_tex3.loadFromFile("images/_ally_spr_3");
    res += _ally_tex4.loadFromFile("images/_ally_spr_4");
    res += _ally_tex5.loadFromFile("images/_ally_spr_5");
    res += _ally_tex6.loadFromFile("images/_ally_spr_6");
    res += _ally_tex7.loadFromFile("images/_ally_spr_7");
    res += _enemy_tex0.loadFromFile("images/_enemy_spr_0");
    res += _enemy_tex1.loadFromFile("images/_enemy_spr_1");
    res += _enemy_tex2.loadFromFile("images/_enemy_spr_2");
    res += _enemy_tex3.loadFromFile("images/_enemy_spr_3");
    res += _enemy_tex4.loadFromFile("images/_enemy_spr_4");
    res += _enemy_tex5.loadFromFile("images/_enemy_spr_5");
    res += _enemy_tex6.loadFromFile("images/_enemy_spr_6");
    res += _enemy_tex7.loadFromFile("images/_enemy_spr_7");
    if (res){
        cout << "Une texture de pellet n'a pas été chargée correctement." << endl;
        exit(1);
    }
}

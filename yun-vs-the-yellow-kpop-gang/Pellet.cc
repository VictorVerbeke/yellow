#include <iostream>
#include <cmath>
#include "Pellet.hh"

using namespace std;

// Les Hitbox de Pellet ont été un véritable CALVAIRE à configurer.
// En effet, une loi dans les shoot'em up dit que si les balles font
// la taille du sprite, le jeu devient soudainement TRES INJUSTE.
// Le sprite étant un carré, nous voulions que la hitbox soit juste au
// bout du sprite, donc on peut remarquer des valeurs dans le constructeur :
// elles sont là à la main pour gérer la hitbox. Croyez-moi, faut pas y toucher.

// Sinon, bah le constructeur à part ça, c'est classique, voir Entity.
Pellet::Pellet(float x, float y, float size, sf::Texture* tex,
               float speed, float direction, int damage, int target)
:
    Entity(x, y, 64, tex, 42, 25, 19, 13),
    _speed(speed),
    _direction(direction),
    _frameNumber(0),
    _frameCounter(0),
    _damage(damage),
    _target(target)
{
        // On modifie l'emplacement de la hitbox grâce à la ligne suivante.
        this->_hitbox.setOrigin(0, -25);
        this->_sprite.rotate(direction);    // On tourne les pellet en direction
        this->_hitbox.rotate(direction);    // de l'endroit où elles vont.
    }

Pellet::~Pellet(){
}

// Dans move(), on fait étonnemment la gestion de l'animation de Pellet.
// En effet, comme move est appelé à chaque frame, on peut mettre la gestion
// de l'animation dedans.
// On déplace le pellet et sa hitbox, puis on incrémente un compteur.
// Si ce compteur atteint trois (trois frames par image d'animation, donc une
// animation à 20 FPS), on passe à l'image suivante.
void Pellet::move(){
    float newX, newY;
    newX = getX() + _speed * cos(_direction * PI /180);
    newY = getY() + _speed * sin(_direction * PI /180);
    setPosition(newX, newY);
    _hitbox.setPosition(newX + cos(_hitbox.getRotation()*PI/180)*40, newY + sin(_hitbox.getRotation()*PI/180)*40);
    _frameCounter++;
    if (_frameCounter == 3) nextFrame();
}

// Switch sur la frame actuelle, on définit donc la suivante.
// Selon la cible, le Pellet a une couleur différente. Si la cible est le
// joueur, le Pellet est rouge, sinon il est bleu.
void Pellet::nextFrame(){
    switch(_frameNumber){
        case 0 :
            _frameNumber = 1;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex1]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex1]));
            break;
        case 1 :
            _frameNumber = 2;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex2]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex2]));
            break;
        case 2 :
            _frameNumber = 3;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex3]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex3]));
            break;
        case 3 :
            _frameNumber = 4;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex4]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex4]));
            break;
        case 4 :
            _frameNumber = 5;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex5]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex5]));
            break;
        case 5 :
            _frameNumber = 6;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex6]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex6]));
            break;
        case 6 :
            _frameNumber = 7;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex7]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex7]));
            break;
        case 7 :
            _frameNumber = 0;
            if (this->_target == 0) this->_sprite.setTexture(*(Textures::texMap[_enemyPellet_tex0]));
            else this->_sprite.setTexture(*(Textures::texMap[_allyPellet_tex0]));
            break;

        default:
            break;
    }
    _frameCounter = 0;
}

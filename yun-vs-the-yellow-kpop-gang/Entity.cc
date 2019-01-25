#include <iostream>
#include "Entity.hh"

using namespace std;

// Le constructeur d'Entity est très long !
// x, y : Emplacement de l'Entity.
// size : taille du carré de texture à prendre.
// tex : Pointeur sur texture (venant de Textures::texMap).
// hitbox_x, hitbox_y : Emplacement du coin supérieur gauche de la hitbox.
// hitbox_width, hitbox_height : Longueur/Largeur de la hitbox.
Entity::Entity (float x, float y, float size, sf::Texture* tex,
                float hitbox_x, float hitbox_y, float hitbox_width, float hitbox_height)
:
    _size(size),
    _x(x),
    _y(y)
{
    (*tex).setSmooth(false); // La texture n'est lissée pour un effet rétro.

    // Le sprite est un carré, de (0, 0) à (size, size) depuis la texture.
    _sprite.setTextureRect(sf::IntRect(0, 0, _size, _size));
    _sprite.setPosition(_x, _y);    // On le positionne en (x,y)
    _sprite.setTexture(*tex);       // On y assigne la texture.

    // La hitbox est un rectangle de taille width x height.
    _hitbox = sf::RectangleShape(sf::Vector2f(hitbox_width, hitbox_height));
    _hitbox.setPosition(hitbox_x, hitbox_y);    // On la positionne, puis on la colore.
    _hitbox.setFillColor(sf::Color(255,255,255, 100)); // pour voir les hitbox en debug
    _sprite.setOrigin(0,0); // On définit les origines du sprite et de la hitbox
    _hitbox.setOrigin(0,0); // dans leur coin supérieur gauche.
}

Entity::~Entity(){

}


// Methodes
// Permet de déplacer l'entité, son sprite et sa hitbox de la même manière.
void Entity::setPosition(float x, float y){
    _x = x;
    _y = y;
    _sprite.setPosition(x, y);
    _hitbox.setPosition(x, y);
}

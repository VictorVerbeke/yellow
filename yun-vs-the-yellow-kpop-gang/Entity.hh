#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.hh"
using namespace std;

class Entity {
    public:
        // Constructeur, destructeur.
        Entity (float x, float y, float size, sf::Texture *tex,
            float hitbox_x, float hitbox_y, float hitbox_width, float hitbox_height);
        ~Entity();

        // Getter, Setter.
        float getX(){ return _x; }
        float getY(){ return _y; }
        float getSize(){ return _size; }
        virtual void setPosition(float x, float y);

        // Toutes les entités peuvent se déplacer. Ajout de deux méthodes
        // virtuelles (move et setPosition n'ont pas la même utilité, l'un
        // déplace selon des variables internes et est différent pour chaque
        // Entity, setPosition la même pour tout le monde et place à un endroit)
        virtual void move() = 0;

        sf::Sprite _sprite;
        sf::RectangleShape _hitbox;
    protected:
        float _size;
        float _x;
        float _y;
};

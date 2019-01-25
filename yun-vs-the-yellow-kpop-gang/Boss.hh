#pragma once
#include "Enemy.hh"
#include "Textures.hh"
#include "Character.hh"
#include "Player.hh"

enum Name { none, Beenzino, GirlGeneration, Jonghyun };

class Boss: public Enemy {
    public:
        // Constructeurs & Destructeurs
        Boss();
        Boss(Name name, sf::Texture* tex);
        ~Boss(); // LVL 1 CROOK

        // Overloads
        void operator-(const float &b);

        // Methodes
        void move();
        Pellet fire(sf::Vector2f targetPos) override;

    private:
        // Attributs.
        Name _name; // Le nom du boss, permet de modifier les stats du genre :
        float _bossFireDamage;  // - les dégats du boss,
        float _bossFireCD;      // - sa vitesse de feu,
        float _bossFireSpeed;   // - la vitesse des Pellet tirés.
};

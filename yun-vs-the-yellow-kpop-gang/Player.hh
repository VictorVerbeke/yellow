#pragma once
#include "Character.hh"
#include "Pellet.hh"
#include "Textures.hh"
#include <iostream>
#include <algorithm>

using namespace std;

class Player: public Character {
    public:

        // Constructeur, destructeur
        Player();
        Player (float x, float y, float size, sf::Texture* tex);
        ~Player();

        // Overload opérateurs
        void operator-(const float &b); // Permet de réduire les HP de b.
        // Dans le cadre de Player, ça permet aussi de faire un flash rouge !
        // C'est plus visuel pour indiquer qu'on prend des dégats.

        // Methodes
        Pellet fire(sf::Vector2f targetPos); // Mais par contre, j'utilise pas
        void decreaseCD();                   // la position de fire(). Ahah.
        void move(int x, int y);

        // J'utilise pas move(), mais si je ne le redéfinis pas, Player
        // est considéré comme une classe abstraite. Alors j'annonce qu'il faut
        // pas utiliser cette méthode.
        void move(){ cout << "Faut pas utiliser move() sur Player, mais move(x, y) !" << endl; };

        // Getter
        unsigned int getFireCD(){ return _fireCD; }
        unsigned int getInvulCD() { return _invulCD; }
        bool getIsHurt() { return _isHurt; }
        // Setter
        void setFireCD(unsigned int newCD) { _fireCD = newCD; }
        void setInvulCD(unsigned int newCD) { _invulCD = newCD; }
        void setIsHurt(bool newBool) { _isHurt = newBool; }

    private:
        // Attributs
        unsigned int _invulCD;           // Nombre de frames d'invincibilité restantes, et
        unsigned int _fireCD;   // nombre de frames à attendre avant de pouvoir tirer.
        bool _isHurt; //Indique si il est touché, pour l'animation !
};

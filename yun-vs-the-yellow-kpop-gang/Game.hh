#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
#include <exception>
#include "Player.hh"
#include "Pellet.hh"
#include "Enemy.hh"
#include "Boss.hh"
#include "PowerUp.hh"

#define PLAYER_SPEED 4

using namespace std;

class Game : public sf::RenderWindow {
    public :
        Game(sf::VideoMode mode, string name);
        ~Game();

        // Methodes du jeu
        void beginGame();
        void checkEvent();
        void scriptedEvents();
        void moveYun();
        void refreshDisplay();
        void enemyAttack();

        // Methodes de collision
        void checkYunCollisions();
        void checkYunCollisionsEnemies();
        void checkYunCollisionsPellets(bool vulnerable);
        void checkYunCollisionsPowerUp();
        void checkEnemyCollisions();
        void checkAllCollisions();

        // Methodes de déplacement
        void moveEntity(Player *object, float x, float y);
        void moveEntity(Boss *object);
        void moveEntity(Enemy *object);
        void moveEntity(PowerUp *object);
        void moveEntity(Pellet *object);
        void moveEntities();

        // Methodes d'affichage
        void drawBackground();
        void drawEntity(Player *object);
        void drawEntity(Boss *object);
        void drawEntity(Enemy *object);
        void drawEntity(PowerUp *object);
        void drawEntity(Pellet *object);
        void drawEntities();

        // Methodes d'ajout d'instances
        void addPelletToVector(Pellet *object);
        void addEnemyToVector(Enemy *object);
        void addPowerUpToVector(PowerUp *object);
        void addBossToVector(Boss *object);

        // Attributs : Sprites
        sf::Sprite _backgroundSprite;
        sf::Texture _backgroundTexture;

        // Attributs : Audio
        sf::Music _music;

        // Attributs : Entités
        Player yun;
        vector<Enemy> enemyVector;
        vector<Pellet> pelletVector;
        vector<PowerUp> pUpVector;
        vector<Boss> bossVector;

        // Attributs : Flags
        bool upFlag;
        bool downFlag;
        bool leftFlag;
        bool rightFlag;
        bool shiftFlag;
        bool firingFlag;

        // Attributs : Controles
        float x;
        float y;
        long int _frameCounter;

    private :

};

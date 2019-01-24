#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <exception>
#include "Player.hh"
#include "Pellet.hh"
#include "Enemy.hh"
#include "Boss.hh"
#include "PowerUp.hh"
#include "Textures.hh"
#define PLAYER_SPEED 4

enum State {beginState = 0,
            mainMenu = 1,  // Je sais que c'est inutile
            options = 2,    // de faire tous ces = i,
            selectLvl = 3,  // cependant je trouve ça plus
            level1 = 4,     // visuel et ça aide pour
            level2 = 5,     // la méthode changeState.
            level3 = 6};

using namespace std;

class Game : public sf::RenderWindow {
    public :
        Game(sf::VideoMode mode, string name);
        ~Game();

        void assignationSprites(sf::Sprite *spr, sf::Texture *tex, int = 800, int = 600);
        // Utilisés dans le constructeur pour initialiser toutes les
        // attributs Sprite des menus, ainsi que les trois textures des panels.

        // Methodes du jeu
        void beginGame();       // Démarre le jeu, boucle principale.
        void enemyAttack();     // Automatise l'attaque des ennemis.
        void bossAttack();
        void moveYun();         // Fait bouger le joueur selon les input
        void goMenuSelection(int sel);  // Permet de naviguer entre les états
                                        // du jeu.

        // Methodes de codage des niveaux scriptés.
        void scriptedEvents_lvl1(); // Permet l'apparition d'ennemis ingame
        void scriptedEvents_lvl2(); // A chaque niveau correspond une série
        void scriptedEvents_lvl3(); // d'apparition, donc des méthodes diff.

        // Methodes de gestions d'Event
        void checkEventMainMenu();  // Selon l'état du jeu (menu principal
        void checkEventSelectLvl(); // selection de niveau, menu d'options
        void checkEventOptions();   // ou encore en jeu, gestion des events
        void checkEventIngame();    // différente.

        // Methodes de collision
        void checkYunCollisions();          // Appelle les fonctions ci-dessous
        void checkYunCollisionsEnemies();   // pour les type d'objet avec
        void checkYunCollisionsPellets(bool vulnerable); // lesquels Yun peut
        void checkYunCollisionsPowerUp();   // interagir.

        void checkEnemyCollisions();    // Check les collisions des ennemis
        void checkBossCollisions();     // Les boss aussi. Pas de discrimination.
        void checkAllCollisions();      // Appelle toutes les détections de
                                        // collision.

        // Methodes de déplacement
        void moveEntity(Player object, float x, float y); // Le joueur se
        void moveEntity(Boss object);      // déplace selon les inputs, mais
        void moveEntity(Enemy object);     // les autres mouvements sont
        void moveEntity(PowerUp object);   // automatiques. Chaque autre entité
        void moveEntity(Pellet object);    // a une vitesse et une direction,
        void moveEntities();                // voir même un pattern de
                                            // déplacement. moveEntities()
                                            // appelle toutes ces méthodes.

        // Methodes d'affichage générales
        void drawMainMenu();    // Selon l'état du jeu où l'on est, il faut
        void drawOptions();     // afficher différentes choses. Pour chaque
        void drawSelectLvl();   // état il y a une fonction courte qui permet
        void drawIngame();      // d'afficher les menus ou le jeu en cours.

        void drawCursor();      // Permet d'afficher le curseur.
        void drawPanel();       // Affiche le panel associé au niveau choisi.
        // Methodes d'affichage Ingame
        void drawBackground();          // En jeu, on veut afficher le fond,
                                            // puis chaque entité. On a do1nc une
        template<class T>                   // méthode pour chaque entité, puis
        void drawEntity (T object);         // une méthode drawEntities pour
        void drawEntities();                // toutes les appeler.


        // Methodes d'ajout d'instances
        void addPelletToVector(Pellet object);     // Les entités (sauf Joueur)
        void addEnemyToVector(Enemy object);       // sont stockées dans des
        void addPowerUpToVector(PowerUp object);   // vecteurs. On les ajoute
        void addBossToVector(Boss object);         // grâce aux fonctions ici.

        // Gestion du son, des niveaux, de la difficulté
        void changeMusic(string musicPath); // Modifie la musique lue
        void changeState(State nextState);  // Modifie l'état du jeu.
        void changeLevel(int i);    // Choisit le niveau suivant ou précédent
        void playRandomKillSound(); // Joue un son de mort au hasard.
        void setVolume(int i);      // Change le volume de +/- 5%
        void setDifficulty(int i);  // Monte ou baisse la difficulté.
        void modifyDifficulty();    // Modifie les attributs statiques des characters.

        // Attributs : Sprites
        sf::Sprite _ingameBG_Spr;       // On a pour tous les menus un sprite
        sf::Sprite _mainMenuBG_Spr;     // pour le fond.
        sf::Sprite _optionsBG_Spr;
        sf::Sprite _selectLvlBG_Spr;
        sf::Sprite _cursor_Spr;
        sf::Sprite _panel_Spr;

        // Attributs : Audio
        sf::Music _music;   // Car c'est important la musique.

        // Attributs : Entités
        Player yun;                     // Ici sont stockées toutes les entités.
        vector<Enemy> enemyVector;      // Yun est unique, mais on peut avoir
        vector<Pellet> pelletVector;    // plein d'entités à l'écran. Ainsi,
        vector<PowerUp> pUpVector;      // on les stocke dans des vecteurs pour
        vector<Boss> bossVector;        // les afficher via itérateurs dans les
                                        // fonctions appropriées.

        // Attributs : Flags
        bool upFlag;        // Utilisés en jeu pour déplacer le personnage
        bool downFlag;      // et déterminer si le joueur est en train d'appuyer
        bool leftFlag;      // sur une touche. Comme sur ordinateur, les
        bool rightFlag;     // event::Key::Pressed fonctionnent en deux temps :
        bool shiftFlag;     // un event au début, puis une série d'events
        bool firingFlag;    // continus plus tard. On préfère utiliser des flags
                            // pour dire qu'on appuie sur (ou relache) une key.
        

        // Attributs : Divers
        float x;    // Correspond à la variation de position du joueur. On fait
        float y;    // une analyse des déplacements, on modifie x et y à plus ou
                    // moins sa vitesse (en #define) et on fait moveYun();
        long int _frameCounter; // Sert à compter le nombre de frames déroulées.
                                // Ca sert pour les événements scriptés.
        int _menuSelection;     // Quel bouton est sélectionné (Menus).
        int _volume;            // Définit le niveau de volume.
        int _difficulty;        // Définit le niveau de difficulté.
        State _selectedLevel;   // Quel niveau est sélectionné (Select Level).

    private:
        State _gameState;   // Etat dans lequel le jeu se trouve.
        sf::Font _font;
        sf::Text _volumeText;
        sf::Text _difficultyText;
        vector<string> _difficultyNames;

        sf::Sound _playerDamageSound;
        sf::Sound _playerKillSound;
        sf::SoundBuffer _bufferDamage1;
        sf::SoundBuffer _bufferDamage2;
        sf::SoundBuffer _bufferKill1;
        sf::SoundBuffer _bufferKill2;
        sf::SoundBuffer _bufferKill3;
        sf::SoundBuffer _bufferKill4;
        sf::SoundBuffer _bufferKill5;
};


template<class T>
void Game::drawEntity (T object) {
    draw(object._sprite);       // A commenter pour voir les hitbox.
    draw(object._hitbox);    // A décommenter pour voir les hitbox.
}

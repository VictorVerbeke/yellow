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

        void assignationSprites(sf::Sprite *spr, sf::Texture *tex,
                                string imagePath, int = 800, int = 600);
        // Utilisé dans le constructeur pour initialiser toutes les
        // attributs Sprite des menus.

        // Methodes du jeu
        void beginGame();       // Démarre le jeu, boucle principale.
        void scriptedEvents();  // Permet l'apparition d'ennemis ingame
        void enemyAttack();     // Automatise l'attaque des ennemis.
        void moveYun();         // Fait bouger le joueur selon les input
        void goMenuSelection(int sel);  // Permet de naviguer entre les états
                                        // du jeu.

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
        void checkAllCollisions();      // Appelle toutes les détections de
                                        // collision.

        // Methodes de déplacement
        void moveEntity(Player *object, float x, float y); // Le joueur se
        void moveEntity(Boss *object);      // déplace selon les inputs, mais
        void moveEntity(Enemy *object);     // les autres mouvements sont
        void moveEntity(PowerUp *object);   // automatiques. Chaque autre entité
        void moveEntity(Pellet *object);    // a une vitesse et une direction,
        void moveEntities();                // voir même un pattern de
                                            // déplacement. moveEntities()
                                            // appelle toutes ces méthodes.

        // Methodes d'affichage générales
        void drawMainMenu();    // Selon l'état du jeu où l'on est, il faut
        void drawOptions();     // afficher différentes choses. Pour chaque
        void drawSelectLvl();   // état il y a une fonction courte qui permet
        void drawIngame();      // d'afficher les menus ou le jeu en cours.

        void drawCursor();      // Permet d'afficher le curseur.

        // Methodes d'affichage Ingame
        void drawBackground();              // En jeu, on veut afficher le fond,
        void drawEntity(Player *object);    // puis chaque entité. On a donc une
        void drawEntity(Boss *object);      // méthode pour chaque entité, puis
        void drawEntity(Enemy *object);     // une méthode drawEntities pour
        void drawEntity(PowerUp *object);   // toutes les appeler.
        void drawEntity(Pellet *object);
        void drawEntities();

        // Methodes d'ajout d'instances
        void addPelletToVector(Pellet *object);     // Les entités (sauf Joueur)
        void addEnemyToVector(Enemy *object);       // sont stockées dans des
        void addPowerUpToVector(PowerUp *object);   // vecteurs. On les ajoute
        void addBossToVector(Boss *object);         // grâce aux fonctions ici.

        // Gestion Musique, Volume, Etat & Niveau, ainsi que Difficulté
        void changeMusic(string musicPath); // Modifie la musique lue
        void changeState(State nextState);  // Modifie l'état du jeu.
        void changeLevel(int i);    // Choisit le niveau suivant ou précédent
        void setVolume(int i);      // Change le volume de +/- 5%
        void setDifficulty(int i);  // Monte ou baisse la difficulté.
        void modifyDifficulty();    // Modifie les attributs statiques des characters.

        // Attributs : Sprites
        sf::Sprite _ingameBG_Spr;       // On a pour tous les menus un sprite
        sf::Texture _ingameBG_Tex;      // pour le fond, ainsi qu'une
        sf::Sprite _mainMenuBG_Spr;     // texture associée. Cela permet
        sf::Texture _mainMenuBG_Tex;    // d'afficher des images et
        sf::Sprite _optionsBG_Spr;      // on draw ensuite les
        sf::Texture _optionsBG_Tex;     // sélections à highlight.
        sf::Sprite _selectLvlBG_Spr;    // BG pour BackGround, Spr pour Sprite,
        sf::Texture _selectLvlBG_Tex;   // Tex pour Texture.
        sf::Sprite _cursor_Spr;         // Celui-là à gauche, c'est pour les
        sf::Texture _cursor_Tex;        // menus, pour indiquer le choix actuel.

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
};

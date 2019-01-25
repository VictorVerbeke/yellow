#pragma once
#include <cmath>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Boss.hh"      // Observez comment les #include de "header.hh" sont à
#include "Enemy.hh"     // la fois rangés en ordre alphabétique, mais aussi en
#include "Pellet.hh"    // ordre de longueur de nom ! Des fois, il y a de
#include "Player.hh"    // la beauté dans les choses inattendues, et il faut
#include "PowerUp.hh"   // savoir l'apprécier. (Promis, les autres commentaires
#include "Textures.hh"  // sont sérieux.)

// State permet de définir les différentes états du jeu (menu principal,
// menu des options, niveaux du jeu, etc...).
enum State {beginState = 0,
            mainMenu = 1,       // Je sais que c'est inutile
            options = 2,        // de faire tous ces = i,
            selectLvl = 3,      // cependant je trouve ça plus
            level1 = 4,         // visuel et ça aide pour
            level2 = 5,         // la méthode changeState.
            level3 = 6};

using namespace std;

class Game : public sf::RenderWindow {
    public :

        // Créateur, destructeur.
        Game(sf::VideoMode mode, string name);
        ~Game();

        void assignationSprites(sf::Sprite *spr, sf::Texture *tex, int = 800, int = 600);
        // Utilisés dans le constructeur pour initialiser toutes les
        // attributs Sprite des menus.

        // Methodes du jeu
        void beginGame();       // Démarre le jeu, boucle principale.
        void enemyAttack();     // Automatise l'attaque des ennemis.
        void bossAttack();      // Pas de jaloux, la même pour les boss.
        void goMenuSelection(int sel);  // Permet de naviguer entre les états
                                        // du jeu.

        // Methodes de codage des niveaux scriptés.
        void scriptedEvents_lvl1();     // Permet l'apparition d'ennemis ingame.
        void scriptedEvents_lvl2();     // A chaque niveau correspond une série
        void scriptedEvents_lvl3();     // d'apparition, donc des méthodes diff.

        // Methodes de gestions d'Event
        void checkEventMainMenu();  // Selon l'état du jeu (menu principal
        void checkEventSelectLvl(); // selection de niveau, menu d'options
        void checkEventOptions();   // ou encore en jeu), gestion des events
        void checkEventIngame();    // différente.

        // Methodes de collision
        void checkYunCollisions();          // Appelle les fonctions ci-dessous
        void checkYunCollisionsEnemies();   // pour les type d'objet avec
        void checkYunCollisionsPellets(bool vulnerable); // lesquels Yun peut
        void checkYunCollisionsPowerUp();   // interagir.
        void checkEnemyCollisions();    // Check les collisions des ennemis et
        void checkBossCollisions();     // des boss.checkAllCollisions()
        void checkAllCollisions();      // appelle toutes les méthodes de
                                        // détection de collision.

        // Methodes de déplacement
        void moveYun();         // Fait bouger le joueur selon les inputs
        void moveEntities();    // enregistrés dans checkEventIngame().
        // Le joueur se déplace selon les inputs, mais les autres mouvements
        // sont automatiques. Chaque autre entité a une vitesse et une
        // direction, voir même un pattern de déplacement.
        // moveEntities() appelle toutes ces méthodes.

        // Methodes d'affichage générales
        void drawMainMenu();    // Selon l'état du jeu où l'on est, il faut
        void drawOptions();     // afficher différentes choses. Pour chaque
        void drawSelectLvl();   // état il y a une fonction courte qui permet
        void drawIngame();      // d'afficher les menus ou le jeu en cours.

        void drawCursor();      // Permet d'afficher le curseur.
        void drawPanel();       // Affiche le panel associé au niveau choisi.

        // Methodes d'affichage Ingame
        void drawBackground();          // En jeu, on veut afficher le fond,
                                        // puis chaque entité. On a donc une
        template<class T>               // méthode pour chaque entité, puis
        void drawEntity (T object);     // une méthode drawEntities pour
        void drawEntities();            // toutes les appeler.


        // Methodes d'ajout d'instances
        void addPelletToVector(Pellet object);     // Les entités (sauf Joueur)
        void addEnemyToVector(Enemy object);       // sont stockées dans des
        void addPowerUpToVector(PowerUp object);   // vecteurs. On les ajoute
        void addBossToVector(Boss object);         // grâce à ces méthodes.

        // Gestion du son, des niveaux, de la difficulté
        void changeMusic(string musicPath); // Modifie la musique lue.
        void changeState(State nextState);  // Modifie l'état du jeu.
        void changeLevel(int i);    // Choisit le niveau suivant ou précédent.
        void playRandomKillSound(); // Joue un son de mort au hasard.
        void setVolume(int i);      // Change le volume de +/- 5%.
        void setDifficulty(int i);  // Monte ou baisse la difficulté.
        void modifyDifficulty();    // Modifie les attributs static de Character.

    private:
        // Attributs : Entités
        Player yun;                     // Ici sont stockées toutes les entités.
        vector<Enemy> enemyVector;      // Yun est unique, mais on peut avoir
        vector<Pellet> pelletVector;    // plein d'entités à l'écran. Ainsi,
        vector<PowerUp> pUpVector;      // on les stocke dans des vecteurs pour
        vector<Boss> bossVector;        // les afficher via itérateurs dans les
                                        // fonctions appropriées. Pour Boss,
                                        // C'est juste que c'est plus pratique.
        // Attributs : Flags
        bool upFlag;        // Utilisés en jeu pour déplacer le personnage
        bool downFlag;      // et déterminer si le joueur est en train d'appuyer
        bool leftFlag;      // sur une touche. Comme sur un ordinateur, les
        bool rightFlag;     // event::Key::Pressed fonctionnent en deux temps :
        bool shiftFlag;     // un event au début, puis une série d'events
        bool firingFlag;    // continus plus tard. On préfère utiliser des flags
                            // pour dire qu'on appuie sur (ou lache) une touche.
        float x;    // Correspond à la variation de position du joueur. On fait
        float y;    // une analyse des déplacements, on modifie x et y à plus ou
                    // moins sa vitesse (en #define) et on fait moveYun();

        // Attributs : Sprites
        sf::Sprite _ingameBG_Spr;       // On a pour tous les menus un sprite
        sf::Sprite _mainMenuBG_Spr;     // pour le fond. C'est plus simple que
        sf::Sprite _optionsBG_Spr;      // de faire un menu bien joli avec
        sf::Sprite _selectLvlBG_Spr;    // plein de sprites. De toute façon,
        sf::Sprite _cursor_Spr;         // la plupart des jeux font ça et
        sf::Sprite _panel_Spr;          // trichent sur leurs menus.

        // Attributs : Navigation et menus
        sf::Font _font;                 // La police des sf::Text.
        sf::Text _volumeText;           // Le texte affiché pour la volume,
        sf::Text _difficultyText;       // le texte affiché pour la difficulté.
        vector<string> _difficultyNames;// Les possibles difficultés sont dedans.
        int _difficulty;        // Définit le niveau de difficulté.
        int _menuSelection;     // Quel bouton est sélectionné (Menus).
        State _gameState;       // Etat dans lequel le jeu se trouve.
        State _selectedLevel;   // Quel niveau est sélectionné dans le menu
                                // Level Select.

        // Attributs : Audio
        int _volume;            // Définit le niveau de volume.
        sf::Music _music;       // Car c'est important la musique.
        sf::Sound _playerDamageSound;   // sf::Sound permet de jouer des sons
        sf::Sound _playerKillSound;     // contenus dans sf::SoundBuffer.
        sf::SoundBuffer _bufferDamage1; // pour chaque effet sonore, on a donc
        sf::SoundBuffer _bufferDamage2; // un buffer, et pour chaque "type"
        sf::SoundBuffer _bufferKill1;   // de son, on a un player associé.
        sf::SoundBuffer _bufferKill2;   // Pour l'histoire, les sons enregistrés
        sf::SoundBuffer _bufferKill3;   // viennent d'une séance destabilisante
        sf::SoundBuffer _bufferKill4;   // où le retour son était décalé d'une
        sf::SoundBuffer _bufferKill5;   // demi-seconde, d'où les paroles...
                                        // ... spéciales.
        // Attributs : Divers
        long int _frameCounter; // Sert à compter le nombre de frames déroulées.
                                // Ca sert pour les événements scriptés.
};

// Fonction utilisant un template.
// (T pouvant être Player, Enemy, Pellet, Boss ou PowerUp)
template<class T>
void Game::drawEntity (T object) {
    draw(object._sprite);       //
    // draw(object._hitbox);    // A décommenter pour voir les hitbox.
    // Pour bien prendre en compte ce changement, il faut faire make clean all.
}

#include "Game.hh"

// Bonjour ! Bienvenue dans la classe Game, où tout se déroule presque.
// Afin de mieux comprendre comment le jeu fonctionne, veuillez vous
// référencer au "Guide au Stagiaire qui devrait reprendre notre projet"
// (il s'agit du PDF rendu avec le mail, c'est le nom secondaire du fichier)
// ou à aller voir le .h où chaque fonction est expliquée brièvement.
// Nous avons essayé de bien commenter afin de rendre le code simple à lire et
// à prendre en main, donc le guide ne sera pas vraiment nécessaire, mais
// (si nous avons le temps de le faire correctement) il y aura peut-être
// des schémas explicatifs de chaque étape du déroulement du jeu.
// Bonne lecture !
//                                Pas longtemps avant la date de rendu,
//                                  - Victor Verbeke, Dimitri Kokkonis.

// Déclaration des variables statiques (par défaut) des classes du jeu.
// Elles sont déclarées ici pour s'y référencer en allant juste en haut
// du fichier. Character regroupe plein de variables concernant les
// caractéristiques des entités héritant de Character (c'est pas pour rien),
// tandis que Textures texMap[egroupe] l'ensemble des textures utilisées dans le jeu.
// Les variables "Character::" sont celles du niveau de difficulté "Normal".
// Les variables "Textures::" sont juste des pointeurs nuls, ils sont
// initialisés dans le main via l'initialisation d'un objet de classe Textures.

float Character::_playerFireCD = 15;
float Character::_playerFireDamage = 10;
float Character::_playerFireSpeed = 1;
float Character::_playerMovementSpeed = 4;
float Character::_playerInvulCD = 60;
float Character::_enemyFireCD = 80;
float Character::_enemyFireDamage = 5;
float Character::_enemyFireSpeed = 4;
float Character::_enemyMovementSpeed = 2;
float Character::_enemyStandardHP = 30;

// Le constructeur de la classe Game. La classe Game consiste en une
// sorte de Superclasse qui dirige toutes les entités du jeu. Elle permet
// de stocker chaque entité générée dans un vecteur associé à la classe,
// de gérer les interactions entre entités, les mouvements des entités
// et l'affichage des entités. Il faut penser à une classe sf::RenderWindow
// à qui on aurait offert les cow power pour gérer le jeu.

// Concernant le constructeur, il initialise une RenderWindow, puis
// affecte à plein d'attributs des valeurs de base, pour qu'ils soient
// utilisés plus tard. Les attributs sont détaillés un par un dans Game.hh.
Game::Game(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name),
    _difficulty(0),
    _menuSelection(0),
    _gameState(beginState),
    _frameCounter(0)
{
    // Configuration de la fenêtre de jeu.
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);

    // Configuration de la musique.
    _music.setLoop(true);
    _volume = 50;

    // Assignations des valeurs de base aux Attributs : Flags
    upFlag = false;     // Chaque flag indique si une touche est enfoncée.
    downFlag = false;   // Par exemple, upFlag indique si la flèche
    rightFlag = false;  // directionnelle Haut est enfoncée.
    leftFlag = false;   // Ces flags sont gérés dans les gestions de touche,
    shiftFlag = false;  // donc dans la partie Event du code. On y reviendra.
    firingFlag = false;

    // Assignations des sprites servant de fond ou de navigation au menu.
    assignationSprites(&_ingameBG_Spr, Textures::texMap[_background_ingame_tex], 1620, 1080);
    assignationSprites(&_mainMenuBG_Spr, Textures::texMap[_background_mainMenu_tex]);
    assignationSprites(&_optionsBG_Spr, Textures::texMap[_background_options_tex]);
    assignationSprites(&_selectLvlBG_Spr, Textures::texMap[_background_selectLvl_tex]);
    assignationSprites(&_cursor_Spr, Textures::texMap[_cursor_tex], 24, 24);
    assignationSprites(&_panel_Spr, Textures::texMap[_panel_lvl1_tex], 390, 290);
    _panel_Spr.setPosition(34, 263);

    // Création des sprites textuels pour le volume et la difficulté.
    stringstream s;
    s << _volume << "%";
    _font.loadFromFile("fonts/OpenSans-Bold.ttf");
    _volumeText.setFont(_font);
    _volumeText.setCharacterSize(50);
    _volumeText.setString(s.str());
    _volumeText.setFillColor(sf::Color::Yellow);
    _volumeText.setPosition(590, 193);

    _difficultyNames.push_back("Easy");
    _difficultyNames.push_back("Normal");
    _difficultyNames.push_back("Hard");
    _difficultyNames.push_back("YUN.");

    _difficultyText.setFont(_font);
    _difficultyText.setCharacterSize(50);
    _difficultyText.setString(_difficultyNames[_difficulty]);
    _difficultyText.setFillColor(sf::Color::Yellow);
    _difficultyText.setPosition(605, 292);


    // Buffers son pour le joueur.
    _bufferDamage1.loadFromFile("sounds/yun_phrases/damage_1.ogg");
    _bufferDamage2.loadFromFile("sounds/yun_phrases/damage_2.ogg");

    _bufferKill1.loadFromFile("sounds/yun_phrases/oui.ogg");
    _bufferKill2.loadFromFile("sounds/yun_phrases/protocole_rip_1.ogg");
    _bufferKill3.loadFromFile("sounds/yun_phrases/protocole_rip_2.ogg");
    _bufferKill4.loadFromFile("sounds/yun_phrases/RIP.ogg");
    _bufferKill5.loadFromFile("sounds/yun_phrases/seine.ogg");
}

// AssignationSprites prend une adresse de sprite, une adresse de texture,
// une taille x et une taille y, et colle tout ça pour créer un sprite avec
// une texture, et tout ça dans un cadre allant de (0,0) à (x,y).
void Game::assignationSprites(sf::Sprite *spr, sf::Texture *tex, int x, int y){
//Orienté vers le bas
    spr->setTexture(*tex);
    spr->setTextureRect(sf::IntRect(0, 0, x, y));
    spr->setPosition(0,0);
    spr->setTexture(*tex);
}

// Rien à voir dans le destructeur.
Game::~Game(){}

// Methode principale : Là où se déroule tout le jeu, beginGame().
void Game::beginGame(){

    // Le menu de départ est le menu principal. On commence aussi avec
    // la difficulté en normal.
    changeState(mainMenu);
    setDifficulty(1);

    // Tant que la fenêtre est ouverte, le programme tourne.
    while (isOpen())
    {
        // Selon l'état du jeu, le jeu se déroule différemment.
        // On peut voir le jeu comme une machine à états : selon son état,
        // son comportement est différent. Il faut voir ça comme le lieu où
        // nous sommes (menu principal, donc comportement de menu principal,
        // le niveau 1 donc comportement de gameplay, etc...).
        switch (_gameState){
            // Cas du menu principal : Capture des inputs, puis affichage.
            case mainMenu:
                checkEventMainMenu();
                drawMainMenu();
                break;

            // Cas des options : Capture des inputs, puis affichage.
            case options:
                checkEventOptions();
                drawOptions();
                break;

            // Cas de la sélection de niveau : Capture des inputs, puis...
            // ...affichage. On se répète un peu, c'est des menus quoi.
            case selectLvl:
                checkEventSelectLvl();
                drawSelectLvl();
                break;

            // Dans le cas du niveau 1, on est plus dans du gameplay. Les
            // événements sont donc plus compliqués. Ca se déroule comme ça :
            case level1:
                checkEventIngame();     // Capture des inputs.
                scriptedEvents_lvl1();  // Evenements scripté (apparition
                                        // ennemis, boss, etc...).
                moveEntities();         // Déplacement des entités.
                checkAllCollisions();   // Vérification des collisions.
                drawIngame();           // Affichage des entités.
                enemyAttack();          // Attaque auto des ennemis.
                bossAttack();           // Attaque auto des boss.
                break;

            case level2:
                checkEventIngame();
                scriptedEvents_lvl2();
                moveEntities();
                checkAllCollisions();
                drawIngame();
                enemyAttack();
                bossAttack();
                break;

            case level3:
                checkEventIngame();
                scriptedEvents_lvl3();
                moveEntities();
                checkAllCollisions();
                drawIngame();
                enemyAttack();
                bossAttack();
                break;
            // Les autres états n'ont pas encore été codés. Il s'agit de
            // niveaux supplémentaires et éventuellement d'un écran de
            // game over, donc rien de folichon non plus. On peut jouer
            // avec un seul niveau.
            default :
                changeState(mainMenu);
                break;
        }
    }
}

// Les événements scriptés, c'est l'apparition à un certain moment d'un
// certain événément : spawn d'ennemi, de boss, de power-up, tout y est.
// A terme, nous aimerions avoir un scriptedEvents() par niveau.
void Game::scriptedEvents_lvl1(){

    // A chaque frame, on incrémente le compteur de frames.
    // Le jeu se déroule à 60 FPS (idéalement), donc on peut considérer que
    // _frameCounter/60 donnerait le nombre de secondes passées.
    _frameCounter++;
    switch (_frameCounter){

        // A 100 frames, donc au bout d'une minute et 66 centièmes en gros,
        case 100 :
            // Création de trois ennemis.
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        // Vous avez l'idée : Frame 500, création de trois ennemis.
        case 500 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 900 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 300, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1000 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1100 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 300, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1500 : // On a essayé de créer différents patterns d'arrivée d'ennemis. Ici, ils sont en ligne.
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 225, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 350, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 475, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1800 : // Ici, ils sont en diagonale.
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(950, 225, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1000, 350, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1050, 475, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 2500 : // Apparition du boss !
            addBossToVector(Boss(Beenzino, Textures::texMap[_boss_tex1]));
            break;

            case 2501 :
                _frameCounter = 2500; // On bloque le jeu à la frame 2500. Une fois
                // le boss vaincu, on peut reprendre le compte.
                break;

            case 2800 : // Après avoir vaincu le boss, le joueur a 300 frames, soit
                changeState(level2);    // cinq secondes, pour aller chercher le
                break;                  // powerup que le boss a fait tomber.

        // Si y'a rien, alors il ne se passe rien. Logique.
        default :
            break;
    }
}

void Game::scriptedEvents_lvl2(){
    _frameCounter++;
    switch (_frameCounter){

        // A 100 frames, donc au bout d'une minute et 66 centièmes en gros,
        case 100 :
            // Création de trois ennemis.
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex2], wave));
            break;

        // Vous avez l'idée.
        case 500 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            break;

        case 900 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 225, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 350, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 475, 32, Character::_enemyStandardHP * 1.25, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1000 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1100 :
            addEnemyToVector(Enemy(1100, 100, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(1100, 400, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 1.5, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1500 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 225, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 350, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 475, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1800 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(950, 225, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1000, 350, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1050, 475, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1100, 475, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1150, 350, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1200, 225, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1250, 100, 32, Character::_enemyStandardHP * 0.75, Textures::texMap[_enemy_tex1], wave));
            break;

        case 2500 :
            addBossToVector(Boss(GirlGeneration, Textures::texMap[_boss_tex2]));

            break;

            case 2501 :
                _frameCounter = 2500; // On bloque le jeu à la frame 2500. Une fois
                // le boss vaincu, on peut reprendre le compte.
                break;

            case 2800 : // Après avoir vaincu le boss, le joueur a 300 frames, soit
                changeState(level3);    // cinq secondes, pour aller chercher le
                break;                  // powerup que le boss a fait tomber.

        // Si y'a rien, alors il ne se passe rien. Logique.
        default :
            break;
    }
}

void Game::scriptedEvents_lvl3(){
    _frameCounter++;
    switch (_frameCounter){

        // A 100 frames, donc au bout d'une minute et 66 centièmes en gros,
        case 100 :
            // Création de trois ennemis.
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex2], wave));
            break;

        // Vous avez l'idée.
        case 500 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 4, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 4, Textures::texMap[_enemy_tex2], wave));
            break;

        case 900 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 225, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 350, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 475, 32, Character::_enemyStandardHP * 1.75, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1000 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1100 :
            addEnemyToVector(Enemy(1100, 100, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(1100, 400, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1500 :
            addEnemyToVector(Enemy(900, 50, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(900, 175, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 300, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(900, 425, 32, Character::_enemyStandardHP * 2, Textures::texMap[_enemy_tex2], wave));
            break;

        case 1800 :
            addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            addEnemyToVector(Enemy(1000, 225, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1100, 350, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1200, 475, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1300, 475, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1400, 350, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1500, 225, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex2], wave));
            addEnemyToVector(Enemy(1600, 100, 32, Character::_enemyStandardHP, Textures::texMap[_enemy_tex1], wave));
            break;

        case 2500 :
            addBossToVector(Boss(Jonghyun, Textures::texMap[_boss_tex3]));
            break;

        case 2501 :
            _frameCounter = 2500; // On bloque le jeu à la frame 2500. Une fois
            // le boss vaincu, on peut reprendre le compte.
            break;

        case 2800 : // Après avoir vaincu le boss, le joueur a 300 frames, soit
            changeState(mainMenu);  // cinq secondes, pour aller chercher le
            break;                  // powerup que le boss a fait tomber.

        // Si y'a rien, alors il ne se passe rien. Logique.
        default :
            break;
    }
}


// Fonction d'attaque de chaque ennemi.
// Pour chaque ennemi dans le vecteur d'ennemi, on appelle la fonction fire().
// L'ennemi tire vers le joueur.  Grâce à la fonction fire, on lui donne un
// cooldown pour éviter qu'il tire en continu. Ensuite, on réduit le cooldown
// pour qu'il puisse tirer de nouveau au bout d'un moment.
void Game::enemyAttack(){
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); itEnemy++){
        if ((*itEnemy).getFireCD() == 0)
            addPelletToVector((*itEnemy).fire(yun._sprite.getPosition()));
        (*itEnemy).decreaseCD();
    }
}

// Même idée, mais pour des boss.
void Game::bossAttack(){
    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); itBoss++){
        if ((*itBoss).getFireCD() == 0)
            addPelletToVector((*itBoss).fire(yun._sprite.getPosition()));
        (*itBoss).decreaseCD();
    }
}

// goMenuSelection(), ça permet de naviguer entre les différents états du jeu.
// Autrement dit, à part quand on est dans un niveau, les menus sont
// naviguables à l'aide d'un curseur. La position du curseur indique le menu
// sélectionné (comme "New Game"). En appuyant sur Entrée ou Espace, on va
// dans le menu désigné.
void Game::goMenuSelection(int sel){

    // Selon l'état du jeu, la sélection a plus ou moins sens.
    switch(_gameState){
        case mainMenu :
            if (sel == 0) changeState(level1);          // Bouton "New Game"
            else if (sel == 1) changeState(selectLvl);  // Bouton "Level Select"
            else if (sel == 2) changeState(options);    // Bouton "Options"
            else if (sel == 3) this->close();           // Bouton "Exit Game"
            break;

        case selectLvl:
            if (sel == 0) changeState(_selectedLevel);  // On accède au niveau.
            else if (sel == 1) changeState(mainMenu);   // Bouton "Main Menu"
            break;

        case options:
            if (sel == 2) changeState(mainMenu);        // Bouton "Main Menu"
            // Les autres boutons n'en sont pas, le sélecteur indique juste
            // l'emplacement du champ à modifier, soit Volume ou Difficulty.
            break;

        // Dans les autres états du jeu, cette fonction ne sert à rien.
        // Elle devrait d'ailleurs ne jamais être appelée.
        default:
            break;
    }
}


// Gestion des events !
// Chaque état à un checkEvent associé. Ils permettent d'enregistrer les
// touches appuyées, puis d'agir en conséquence : modifier des flags ou
// appeler des fonctions.

// Events du menu principal
void Game::checkEventMainMenu(){

    sf::Event event;
    while(pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                close();
                break;

            // Pour l'histoire du (x+3)%4, ça équivaut juste à un (x-1)%4.
            // Pour une raison obscure, ça ne marche pas en faisant (x-1)%4...
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up) _menuSelection = (_menuSelection + 3)%4;
                if (event.key.code == sf::Keyboard::Down) _menuSelection = (_menuSelection + 1)%4;
                if (event.key.code == sf::Keyboard::Return) goMenuSelection(_menuSelection);
                if (event.key.code == sf::Keyboard::Space) goMenuSelection(_menuSelection);
                if (event.key.code == sf::Keyboard::Escape) close();
                break;

            default:
                break;
        }
    }
}

// Events du menu des options
void Game::checkEventOptions(){

    sf::Event event;
    while(pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                close();
                break;

            // Le code devient un peu plus moche ici.
            // Les effets des touches dépendent aussi de l'endroit sélectionné.
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up) _menuSelection = (_menuSelection + 2) % 3;
                if (event.key.code == sf::Keyboard::Down) _menuSelection = (_menuSelection + 1)%3;

                // Dans le cas de droite, il augmente le son OU la difficulté
                // selon la position du curseur ("Volume" ou "Difficulty").
                if (event.key.code == sf::Keyboard::Left)
                {
                    if (_menuSelection == 0) setVolume(-1);     // Baisser le volume
                    if (_menuSelection == 1) setDifficulty(-1); // Baisser la difficulté
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    if (_menuSelection == 0) setVolume(1);      // Augmenter le volume
                    if (_menuSelection == 1) setDifficulty(1);  // Augmenter la difficulté
                }

                if (event.key.code == sf::Keyboard::Return) goMenuSelection(_menuSelection);
                if (event.key.code == sf::Keyboard::Space) goMenuSelection(_menuSelection);
                if (event.key.code == sf::Keyboard::Escape) changeState(mainMenu);
                break;

            default:
                break;
        }
    }
}

// Events du Level Select
void Game::checkEventSelectLvl(){

    sf::Event event;
    while(pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up) _menuSelection = (_menuSelection + 1)%2;
                else if (event.key.code == sf::Keyboard::Down) _menuSelection = (_menuSelection + 1)%2;
                else if (event.key.code == sf::Keyboard::Left) changeLevel(-1); // Affiche le niveau précédent
                else if (event.key.code == sf::Keyboard::Right) changeLevel(1); // Affiche le niveau suivant
                else if (event.key.code == sf::Keyboard::Return) goMenuSelection(_menuSelection);
                else if (event.key.code == sf::Keyboard::Space) goMenuSelection(_menuSelection);
                else if (event.key.code == sf::Keyboard::Escape) changeState(mainMenu);
                break;

            default:
                break;
        }
    }
}

void Game::checkEventIngame(){

    sf::Event event;

    while (pollEvent(event))
    {
        switch (event.type) {
                case sf::Event::Closed:
                // "close requested" event: we close the window
                close();
                break;

            case sf::Event::KeyPressed:
                // De manière assez rigolote, rester appuyer n'active pas
                // l'event KeyPressed à chaque frame. Il s'active une fois,
                // puis à chaque frame mais au bout d'un certain temps.
                // On considère donc qu'à l'appui, on active le flag, et on
                // attend qu'elle soit relachée pour désactiver le flag.
                // Sauf pour Echap. Ca, ça renvoit au menu principal.
                if (event.key.code == sf::Keyboard::Up) upFlag = true;
                if (event.key.code == sf::Keyboard::Down) downFlag = true;
                if (event.key.code == sf::Keyboard::Left) leftFlag = true;
                if (event.key.code == sf::Keyboard::Right) rightFlag = true;
                if (event.key.code == sf::Keyboard::LShift) shiftFlag = true;
                if (event.key.code == sf::Keyboard::Space) firingFlag = true;
                if (event.key.code == sf::Keyboard::Escape) changeState(mainMenu);
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) upFlag = false;
                if (event.key.code == sf::Keyboard::Down) downFlag = false;
                if (event.key.code == sf::Keyboard::Left) leftFlag = false;
                if (event.key.code == sf::Keyboard::Right) rightFlag = false;
                if (event.key.code == sf::Keyboard::LShift) shiftFlag = false;
                if (event.key.code == sf::Keyboard::Space) firingFlag = false;
                break;

            default:
                break;
        }
    }
    // Si on appuie sur tirer, pew pew.
    if (firingFlag) if (yun.getFireCD() == 0) addPelletToVector(yun.fire(yun._sprite.getPosition()));
}


// Methodes de collision
// Actuellement, on regarde les collisions des sprites. Il faut que je fasse
// des hitbox car sinon elles sont trop grandes, car basées sur les rectangles
// des sprites, basés sur les images qu'on fournit. C'est un TODO.

// Vérification des collisions du joueur !
// Si Yun est en frame d'invincibilité, alors il prend aucun dégat mais
// supprime tous les pellets touchés. Sinon, il prend des dégats de la part
// des ennemis ou des pellets.
void Game::checkYunCollisions(){
    if (yun.getInvulCD() == 0)
    {
        checkYunCollisionsEnemies();        // Pour les ennemis
        checkYunCollisionsPellets(true);    // Pour les balles.

        // On affecte à chaque frame un son aléatoire pour quand Yun se
        // fera toucher. Il en a deux, mais ils sont rigolos.
        if (rand() > RAND_MAX / 2)
            _playerDamageSound.setBuffer(_bufferDamage1);
        else
            _playerDamageSound.setBuffer(_bufferDamage2);
        _playerDamageSound.play();  // On joue le son.
    }
    else
    {
        yun.setInvulCD(yun.getInvulCD() - 1);   // On réduit le temps
        if (yun.getIsHurt() == true){           // d'invincibilité. Si il s'agit
            yun.setIsHurt(false);               // de la deuxième frame
        // d'invincibilité, alors on modifie la texture pour indiquer qu'il est
        // blessé. La première frame est un Yun rouge, pour montrer la frame où
        // il est blessé (check l'overload de Player pour ça).
            yun._sprite.setTexture(*(Textures::texMap[_yun_hurt_tex]));
        }
        // A la dernière frame, on remet Yun tranquille content (il peut donc
        // de nouveau se faire taper par les stars de K-pop).
        if (yun.getInvulCD() == 0){
            yun._sprite.setTexture(*(Textures::texMap[_yun_still_tex]));
        }
        checkYunCollisionsPellets(false); // False correspond à "Il ne peut pas
        // se faire blesser par les balles, car invulnérable".
    }

    // Collision avec les powerUp.
    checkYunCollisionsPowerUp();

    // Si Yun meurt, alors on le dit dans le terminal, et on retourne au
    // menu principal.
    if (yun.getHp() < 0){
        cout << "Yun est mort de mauvais gout ! Retour au menu principal !" << endl;
        changeState(mainMenu);
    }
}


void Game::checkYunCollisionsEnemies(){

    // Si yun n'est pas invulnérable, il prend des dégats des ennemis.
    // Pour chaque Enemy du vecteur Enemy, si il y a collision,
    // alors Yun prend des dégats (via la surcharge -(const &float)).
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); itEnemy++){
        if (yun._hitbox.getGlobalBounds().intersects((*itEnemy)._hitbox.getGlobalBounds()))
        {
            yun - (Character::_enemyFireDamage * 2);
        }
    }

    // Au passage, il prend la même chose de la part des boss.
    // Juste, ça fait plus mal.
    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); itBoss++){
        if (yun._hitbox.getGlobalBounds().intersects((*itBoss)._hitbox.getGlobalBounds()))
        {
            yun - (Character::_enemyFireDamage * 5);
        }
    }
}

// Si Yun est vulnérable (true), alors il prend des dégats.
// Dans les deux cas, il supprime les pellets touchés.
void Game::checkYunCollisionsPellets(bool vulnerable){

    // Pseudo-code équivalent :
    //  Pour chaque pellet dans le vecteur de pellet :
    //      | Si la cible du Pellet est bien Yun :
    //      |    | Si il y a collision des hitbox :
    //      |    |    | Si Yun est vulnérable :
    //      |    |    |    | Yun prend des dégats,
    //      |    |    |    | On supprime le pellet du vecteur de pellets.
    //      |    |    | On supprime le pellet.
    //      |    | Sinon, pellet suivant.
    //      | Sinon, pellet suivant.
    //  Fin Pour.

    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); )
    {
        if ((*itPellet).getTarget() == 0) // Si les pellets visent Yun
        {
            if (yun._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds()))
            {
                if (vulnerable) yun - (*itPellet).getDamage();  // Il prend des dégats
                itPellet = pelletVector.erase(itPellet); // On supprime le pellet.
            } else itPellet++;
        } else itPellet++;
    }
}

// Si Yun touche un powerup, il est amélioré durant TOUTE la partie.
void Game::checkYunCollisionsPowerUp(){

    // Pseudo-code équivalent de la fonction :
    //  Pour chaque powerUp dans le vecteur de powerUps :
    //      | Si il y a collision des hitboxs :
    //      |    | Selon le type, les caractéristiques de Yun sont améliorées.
    //      |    | On affiche dans le terminal les caractéristiques de Yun.
    //      |    | On efface le powerUp du vecteur de powerUps.
    //      | Sinon, on va au powerUp suivant.
    //  Fin Pour.

    vector<PowerUp>::iterator itPowerUp = pUpVector.begin();
    for ( ; itPowerUp != pUpVector.end(); )
    {
        if (yun._hitbox.getGlobalBounds().intersects((*itPowerUp)._hitbox.getGlobalBounds()))
        {
            switch((*itPowerUp).getType()){
                case power :
                    Character::_playerFireDamage += (*itPowerUp).getPower();
                    break;
                case speed :
                    Character::_playerMovementSpeed += (*itPowerUp).getPower()/5;
                    break;
                case invul :
                    Character::_playerInvulCD += (*itPowerUp).getPower();
                    break;
                default :
                    break;
            }
            itPowerUp = pUpVector.erase(itPowerUp); // On supprime le powerUp.
            cout << "\tUpdate des caractéristiques du joueur :" << endl;
            cout << "\tDégats des projectiles : " << Character::_playerFireDamage << " HP" << endl;
            cout << "\tVitesse de déplacement : " << Character::_playerMovementSpeed * 25  << " %" << endl;
            cout << "\tFrames d'invulnérabilité : " << Character::_playerInvulCD << " frames"<< endl << endl;
        } else itPowerUp++;
    }
}

// Si un ennemi rencontre un pellet tiré par le joueur, alors il est blessé.
// Pour les dégats de l'ennemi, voir la surcharge de l'opérateur - dans Enemy.
void Game::checkEnemyCollisions(){

    bool enemyKilled = false;

    // Les ennemis ne sont blessés que par les pellets tirés par Yun.
    // Retranscription de ce qu'il y a en-dessous :
    //
    // Pour chaque ennemi dans le vecteur d'ennemi :
    // 1 : Pour chaque Pellet dans le vecteur de Pellet :
    //   - Si l'ennemi est pas mort :
    //     - Si la cible visée par le Pellet est bien un ennemi :
    //       - Si les hitbox des deux entités se superposent :
    //          - Alors l'ennemi prend des dégats !
    //          - On efface le Pellet.
    //          - Si l'ennemi n'a plus de vie, alors il est tué. (logique)
    //        - Sinon, on va au Pellet suivant.
    //      - Sinon, on va au Pellet suivant. (Echo, echo)
    //    - Sinon, on va à la fin du vecteur de pellet.
    // 2 : Si l'ennemi est mort :
    //   - On crée (peut-être, 50% de chance) un power-up et on l'ajoute au jeu
    //   - On supprime l'ennemi du vecteur d'ennemis
    //   - On joue un son de mort (Yun qui dit une phrase).
    // 3 : Y'a pas de trois, c'est fini.

    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        enemyKilled = false;
        vector<Pellet>::iterator itPellet = pelletVector.begin();
        for ( ; itPellet != pelletVector.end(); ){
            if (enemyKilled == false){
                if ((*itPellet).getTarget() == 1){
                    if ((*itEnemy)._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds())){
                        (*itEnemy) - (*itPellet).getDamage();
                        itPellet = pelletVector.erase(itPellet);
                        if ((*itEnemy).getHp() <= 0) enemyKilled = true;
                    } else itPellet++;
                } else itPellet++;
            } else itPellet = pelletVector.end();
        }

        if (enemyKilled == false) itEnemy++;
        else {
            int i = rand()%6;
            switch (i){     // Ici, on crée un power-up au hasard : une chance
                case 0 :    // sur deux à chaque ennemi tué de pop.
                addPowerUpToVector(PowerUp((*itEnemy).getX(), (*itEnemy).getY(),
                                   Textures::texMap[_pUp_power_tex], power, 2));
                    break;
                case 1 :
                addPowerUpToVector(PowerUp((*itEnemy).getX(), (*itEnemy).getY(),
                                   Textures::texMap[_pUp_speed_tex], speed, 2));
                    break;
                case 2 :
                addPowerUpToVector(PowerUp((*itEnemy).getX(), (*itEnemy).getY(),
                                   Textures::texMap[_pUp_invul_tex], invul, 2));
                    break;
                default:
                    break;
            }
            itEnemy = enemyVector.erase(itEnemy);
            playRandomKillSound(); // Enemy killed, play a victory sound
        }
    }
}

void Game::checkBossCollisions(){

    // C'est la même idée que pour l'ennemi. La différence est que
    // le boss donne obligatoirement un powerUp de dégats, très puissant. (+5)

    bool isKilled = false;
    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); ){
        isKilled = false;
        vector<Pellet>::iterator itPellet = pelletVector.begin();
        for ( ; itPellet != pelletVector.end(); ){
            if (isKilled == false){
                if ((*itPellet).getTarget() == 1){
                    if ((*itBoss)._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds())){
                        (*itBoss) - (*itPellet).getDamage();
                        itPellet = pelletVector.erase(itPellet);
                        if ((*itBoss).getHp() <= 0) isKilled = true;
                    } else itPellet++;
                } else itPellet++;
            } else itPellet++;
        }

        if (isKilled == false) itBoss++;
        else {
            _frameCounter++;
            addPowerUpToVector(PowerUp((*itBoss).getX(), (*itBoss).getY(),
                               Textures::texMap[_pUp_power_tex], power, 5));
            itBoss = bossVector.erase(itBoss);
            playRandomKillSound(); // Enemy killed, play a victory sound
        }
    }
}

// Appel de toutes les fonctions de collisions vues précédemment.
void Game::checkAllCollisions(){
    checkYunCollisions();
    checkEnemyCollisions();
    checkBossCollisions();
}


// Methodes de déplacement !
// Toutes les classes possèdent un moyen de se déplacer : Yun manuellement
// grace à move(x,y), contrairement aux autres entités qui se déplace avec
// move() qui fait appel à leurs attributs protégés. A chaque frame, on fait
// bouger les entités avec les fonctions suivantes.

// moveYun permet de bouger Yun.
// Cette méthode utilise les flags modifiés dans checkEventIngame().
void Game::moveYun(){

    // Yun va bouger : ces deux variables correspondent à ses déplacements.
    // Selon les flags, ils vont être modifiés, donc on peut considérer que
    // ce sont plus des dx et dy que x et y, mais peu importe.
    x = 0;
    y = 0;

    // Si on appuie sur gauche et qu'on est pas sur le rebord gauche, alors
    // on peut bouger vers la gauche. Même idée pour les quatre directions.
    if (leftFlag && (yun.getX()) > 0) x -= Character::_playerMovementSpeed;
    if (rightFlag && (yun.getX() + yun.getSize())< getSize().x) x += Character::_playerMovementSpeed;
    if (upFlag && (yun.getY()) > 0) y -= Character::_playerMovementSpeed;
    if (downFlag && (yun.getY() + yun.getSize()) < getSize().y) y += Character::_playerMovementSpeed;

    if (shiftFlag){     // Si on appuie sur Shift, on peut naviguer plus
        x = x/2;        // lentement. Utile lors des situations délicates où
        y = y/2;        // on doit naviguer entre les balles, ou quand on a
    }                   // une vitesse trop élevée grâce aux power-ups.

    yun.move(x, y);     // Comme la fonction moveYun est appelée à chaque
    yun.decreaseCD();   // frame, on en profite pour faire réduire son
                        // cooldown d'attaque ici.
}

// Somme de toutes les déplacements d'entités.
void Game::moveEntities(){

    moveYun(); // On fait bouger Yun.

    // C'est la même idée pour les quatre vecteurs. Je vais pas recréer
    // une fonction pour chaque itérateur, l'idée est simple et les blocs sont
    // assez espacés pour comprendre. Voici quand même une explication pour
    // l'un des vecteurs :

    // Pour tous les Enemy dans le vecteur d'Enemy, on les fait bouger.
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        // Si l'ennemi sort de l'écran, on le supprime du vecteur.
        // Sinon, on le fait bouger.
        if ((*itEnemy).getX() < -(*itEnemy).getSize() || (*itEnemy).getY() < -(*itEnemy).getSize() || (*itEnemy).getY() > getSize().y){
            itEnemy = enemyVector.erase(itEnemy);
        } else {
            (*itEnemy).move();
            itEnemy++;
        }
    }


    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); ){
        if ((*itPellet).getX() < 0 || (*itPellet).getX() > getSize().x || (*itPellet).getY() < 0 || (*itPellet).getY() > getSize().y){
            itPellet = pelletVector.erase(itPellet);
        } else {
            (*itPellet).move();
            itPellet++;
        }
    }

    vector<PowerUp>::iterator itPowerUp = pUpVector.begin();
    for ( ; itPowerUp != pUpVector.end(); ){
        if ((*itPowerUp).getX() < 0 || (*itPowerUp).getX() > getSize().x || (*itPowerUp).getY() < 0 || (*itPowerUp).getY() > getSize().y){
            itPowerUp = pUpVector.erase(itPowerUp);
        } else {
            (*itPowerUp).move();
            itPowerUp++;
        }
    }

    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); ){
        if ((*itBoss).getX() < 0 || (*itBoss).getX() > getSize().x || (*itBoss).getY() < 0 || (*itBoss).getY() > getSize().y){
            itBoss = bossVector.erase(itBoss);
        } else {
            (*itBoss).move();
            itBoss++;
        }
    }
}


// Methodes d'affichage générales !
// Pour chaque état du jeu, on a des méthodes d'affichage différentes.

// Par exemple, pour le menu principal :
// -> On efface et ajoute un fond de couleur unie.
// -> On ajoute la texture de fond
// -> On ajoute le curseur.
// -> On affiche le tout.
void Game::drawMainMenu(){
    clear(sf::Color(0,127,0));
    draw(_mainMenuBG_Spr);
    drawCursor();
    display();
}

void Game::drawOptions(){
    clear(sf::Color(127,0,0));
    draw(_optionsBG_Spr);
    draw(_volumeText);      // On affiche les textes.
    draw(_difficultyText);
    drawCursor();
    display();
}

void Game::drawSelectLvl(){
    clear(sf::Color(0,0,127));
    draw(_selectLvlBG_Spr);
    draw(_panel_Spr);   // On affiche les images des niveaux.
    drawCursor();
    display();
}

void Game::drawIngame(){
    // Clear the window and apply grey background
    clear(sf::Color(0,0,0));
    drawBackground();   // On affiche le background.
    drawEntities();     // On affiche les entités
    drawGUI();          // On affiche le GUI (barres de vie)
    display();
}

// Selon l'état du jeu et la sélection du menu (le bouton visé), on
// déplace le curseur à l'écran. Toutes les valeurs sont faites à la main,
// donc veuillez ne pas y toucher ! Enfin vous pouvez, mais à vous de les
// remettre après.
void Game::drawCursor(){
    // Dépend du State et de _menuSelection.
    switch(_gameState){
        case mainMenu :
            if (_menuSelection == 0) _cursor_Spr.setPosition(597, 462);
            if (_menuSelection == 1) _cursor_Spr.setPosition(577, 496);
            if (_menuSelection == 2) _cursor_Spr.setPosition(640, 530);
            if (_menuSelection == 3) _cursor_Spr.setPosition(607, 564);
            break;

        case selectLvl :
            if (_menuSelection == 0) _cursor_Spr.setPosition(542, 366);
            if (_menuSelection == 1) _cursor_Spr.setPosition(501, 463);
            break;

        case options :
            if (_menuSelection == 0) _cursor_Spr.setPosition(340, 215);
            if (_menuSelection == 1) _cursor_Spr.setPosition(340, 315);
            if (_menuSelection == 2) _cursor_Spr.setPosition(470, 460);
            break;

        default: // On le sort de l'écran, comme ça on le voit pas.
            _cursor_Spr.setPosition(-100, -100);
            break;
    }
    draw(_cursor_Spr);
}

// Methodes d'affichage Ingame !

// On veut que le background défile en fond.
// On fait donc en sorte que l'image soit basée sur le temps passé en jeu.
// Vu que le _frameCounter est bloqué en jeu, ça bloque aussi le fond durant
// les combats de Boss.
void Game::drawBackground(){
    draw(_ingameBG_Spr);
    _ingameBG_Spr.setPosition(-0.1*_frameCounter, 0);
}

// Méthode d'appel des différentes méthodes d'affichage des entités.
void Game::drawEntities(){

    // Pour chaque entité dans chaque vecteur, on affiche l'entité.
    // drawEntity() vient de RenderWindow, dont Game hérite.
    for(vector<Enemy>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++)
        drawEntity((*it));
    for(vector<Boss>::iterator it = bossVector.begin(); it != bossVector.end(); it++)
        drawEntity((*it));
    for(vector<PowerUp>::iterator it = pUpVector.begin(); it != pUpVector.end(); it++)
        drawEntity((*it));
    for(vector<Pellet>::iterator it = pelletVector.begin(); it != pelletVector.end(); it++)
        drawEntity((*it));
    // Draw the Player after everything.
    drawEntity(yun);     // Les commentaires en anglais c'est Dimitri, il
                         // a vraiment les habitudes d'un pro.
}


// Méthode qui dessine le GUI (barres de vie) sur l'écran.
void Game::drawGUIYun ()
{
    sf::Text yunHP;
    sf::RectangleShape outlineBarreVieYun(sf::Vector2f(200.f, 25.f));
    sf::RectangleShape barreVieYun(sf::Vector2f(yun.getHp() * 2, 25.f));

    outlineBarreVieYun.setPosition(140, 20);
    outlineBarreVieYun.setOutlineThickness(5.f);
    outlineBarreVieYun.setOutlineColor(sf::Color(40, 40, 40, 255));
    outlineBarreVieYun.setFillColor(sf::Color(0, 0, 0, 0));

    barreVieYun.setPosition(140, 20);
    barreVieYun.setFillColor(sf::Color::Green);

    yunHP.setFont(_font);
    yunHP.setCharacterSize(20);
    yunHP.setString("Yun's HP:");
    yunHP.setPosition(20, 20);

    draw(yunHP);
    draw(barreVieYun);
    draw(outlineBarreVieYun);
}


void Game::drawGUIBoss ()
{
    sf::Text bossHP;


    bossHP.setFont(_font);
    bossHP.setCharacterSize(20);
    bossHP.setString("Boss's HP:");
    bossHP.setPosition(500, 550);



    draw(bossHP);
}


void Game::drawGUI ()
{
    drawGUIYun();
    if (bossVector.size() > 0) drawGUIBoss();
}

// Methodes d'ajout d'entités dans les vecteurs de la classe Game.
// Généralement on fait addXToVector(X(...)).
void Game::addPelletToVector(Pellet object){
    pelletVector.push_back(object);
}

void Game::addEnemyToVector(Enemy object){
    enemyVector.push_back(object);
}

void Game::addPowerUpToVector(PowerUp object){
    pUpVector.push_back(object);
}

void Game::addBossToVector(Boss object){
    bossVector.push_back(object);
}

// Gestion _gameState !
// Permet d'affecter l'attribut _gameState, puis change les musiques,
// les vecteurs, et d'autres valeurs selon l'état actuel et le suivant.
void Game::changeState(State nextState){
    _frameCounter = 0;      // Réinitialisation du compteur de frames et
    _menuSelection = 0;     // du menu sélectionné (pour la navigation entre
    yun.setHp(100);         // menus au début du jeu). On restaure aussi la vie
                            // du joueur.
    switch (nextState){     // Selon l'état où on se dirige ! (et pas celui où
                            // on est !!)
        case level1 :
            // Si on vient du menu principal ou de la sélection de niveau,
            // autrement dit si il s'agit de notre premier niveau.
            if (_gameState == mainMenu || _gameState == selectLvl) {
                modifyDifficulty(); // On reset les caractéristiques.
                cout << "Bienvenue en jeu ! Votre mission : Tuer la K-Pop !" << endl;
            }
            cout << "\t - - - [Niveau 1 - vs Beenzino] - - -" << endl;
            enemyVector.clear();    // On nettoie les vecteurs, pour éviter
            pelletVector.clear();   // d'avoir les ennemis/balles/powerUps
            pUpVector.clear();      // des anciens niveaux.
            bossVector.clear();
            yun.setPosition(100, 274);  // On dit à Yun de se mettre en place.
            changeMusic("sounds/musics/beenzino.ogg"); // On joue une musique.
            _gameState = nextState; // On met à jour l'état actuel.
            break;

        case level2 :
            // C'est la même idée pour tous les niveaux.
            if (_gameState == mainMenu || _gameState == selectLvl) {
            modifyDifficulty();
                cout << "Bienvenue en jeu ! Votre mission : Tuer la K-Pop !" << endl;
            }
            cout << "\t - - - [Niveau 2 - vs Girl's Generation] - - -" << endl;
            enemyVector.clear();
            pelletVector.clear();
            pUpVector.clear();
            bossVector.clear();
            yun.setPosition(100, 274);
            changeMusic("sounds/musics/girlgeneration.ogg");
            _gameState = nextState;
            break;

        case level3 :
            if (_gameState == mainMenu || _gameState == selectLvl) {
            modifyDifficulty();
                cout << "Bienvenue en jeu ! Votre mission : Tuer la K-Pop !" << endl;
            }
            cout << "\t - - - [Niveau 3 - vs Jonghyun] - - -" << endl;
            enemyVector.clear();
            pelletVector.clear();
            pUpVector.clear();
            bossVector.clear();
            yun.setPosition(100, 274);
            changeMusic("sounds/musics/jonghyun.ogg");
            _gameState = nextState;
            break;

        case selectLvl : // Menu de sélection de niveau !
            _selectedLevel = level1; // Petit hack pour toujours afficher le
            changeLevel(1);     // premier niveau en arrivant sur le menu :
            changeLevel(-1);    // mettre au niveau 1, avancer puis reculer pour
                                // mettre à jour l'affichage.
        case mainMenu :
        case options :
            // Si on démarre le jeu ou si on revient d'un niveau de jeu, on met la musique des menus.
            if ((_gameState == beginState) || (_gameState == level3) || (_gameState == level2) || (_gameState == level1))
                changeMusic("sounds/musics/main_menu_music.ogg");
            _gameState = nextState;
            break;

        // Sinon, on fait rien.
        default:
            break;
    }
}

// Cette méthode permet de changer de musique.
// Le musicPath est le chemin du fichier à lire.
void Game::changeMusic(string musicPath){

    _music.pause();
    if (!_music.openFromFile(musicPath)){
        cerr << "Failed to open music : " << musicPath << endl;
        exit(1);
    }
    _music.play();
}

// Méthode qui permet de modifier l'image du niveau sélectionné.
// On invoque changeLevel(-1) ou (1) pour aller respectivement au niveau
// précédent ou suivant. Il faut savoir que ça change juste la sélection
// du niveau et ça ne le charge pas. On passe par changeState pour change
// de niveau.
void Game::changeLevel(int i){

    switch(_selectedLevel){
        case level1 :
            if (i > 0){
                _panel_Spr.setTexture(*(Textures::texMap[_panel_lvl2_tex]));
                _selectedLevel = level2;
            }

            break;

        case level2 :
            if (i > 0) {
                _panel_Spr.setTexture(*(Textures::texMap[_panel_lvl3_tex]));
                _selectedLevel = level3;
            }
            if (i < 0) {
                _panel_Spr.setTexture(*(Textures::texMap[_panel_lvl1_tex]));
                _selectedLevel = level1;
            }
            break;

        case level3 :
            if (i < 0) {
                _panel_Spr.setTexture(*(Textures::texMap[_panel_lvl2_tex]));
                _selectedLevel = level2;
            }
            break;

        default :
            break;
    }
}

// Cette méthode joue un son aléatoire de Yun qui tue un ennemi.
// Elle est invoquée quand Yun tue un ennemi.
void Game::playRandomKillSound(){
    // Choose a random number between 0 and 4
    int min = 0;
    int max = 4;
    int random_sound = min + (rand() % static_cast<int>(max - min + 1));

    // Assing a sound buffer according to the number
    switch (random_sound) {
        case 0:
            _playerKillSound.setBuffer(_bufferKill1);
            break;
        case 1:
            _playerKillSound.setBuffer(_bufferKill2);
            break;
        case 2:
            _playerKillSound.setBuffer(_bufferKill3);
            break;
        case 3:
            _playerKillSound.setBuffer(_bufferKill4);
            break;
        case 4:
        default:
            _playerKillSound.setBuffer(_bufferKill5);
            break;
    }

    // Play the sound
    _playerKillSound.play();
}

// Change le volume de la musique.
void Game::setVolume(int i){
    if (i > 0){
        if (_volume < 100) _volume += 1; // Par tranches de 1%, mais quand on
    }                                    // reste appuyé, ça va vite.
    else if (i < 0){
        if (_volume > 0) _volume -= 1;
    }

    stringstream s;

    s << _volume << "%"; // De la forme "60%" par exemple.
    _playerKillSound.setVolume(_volume);    // On modifie le volume des effets
    _playerDamageSound.setVolume(_volume);  // sonores, ainsi que de la musique.
    _music.setVolume(_volume);
    _volumeText.setString(s.str()); // On affiche le volume sous forme de texte.
}

// Même idée que pour changeLevel : +1 pour monter la difficulté,
// -1 pour la descendre.
void Game::setDifficulty(int i){
    // La difficulté va de 0 (easy) à 3 (yun, soit very hard)
    if (i > 0) if (_difficulty < 3) _difficulty++;
    if (i < 0) if (_difficulty > 0) _difficulty--;
    modifyDifficulty();
    _difficultyText.setString(_difficultyNames[_difficulty]);
}

// Modifie toutes les variables liées à la difficulté.
void Game::modifyDifficulty(){

    // To change the color of the difficulty text
    sf::Color orange(255, 132, 26, 255);

    switch (_difficulty)
    {
        case 0 :
            Character::_playerFireCD = 15;
            Character::_playerFireDamage = 50;
            Character::_playerFireSpeed = 10;
            Character::_playerMovementSpeed = 4;
            Character::_playerInvulCD = 100;
            Character::_enemyFireCD = 120;
            Character::_enemyFireDamage = 5;
            Character::_enemyFireSpeed = 2;
            Character::_enemyMovementSpeed = 2;
            Character::_enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setFillColor(sf::Color::Green);
            break;

        case 1 :
            Character::_playerFireCD = 15;
            Character::_playerFireDamage = 20;
            Character::_playerFireSpeed = 10;
            Character::_playerMovementSpeed = 4;
            Character::_playerInvulCD = 60;
            Character::_enemyFireCD = 80;
            Character::_enemyFireDamage = 5;
            Character::_enemyFireSpeed = 3;
            Character::_enemyMovementSpeed = 2;
            Character::_enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setFillColor(sf::Color::Yellow);
            break;

        case 2 :
            Character::_playerFireCD = 15;
            Character::_playerFireDamage = 15;
            Character::_playerFireSpeed = 10;
            Character::_playerMovementSpeed = 4;
            Character::_playerInvulCD = 40;
            Character::_enemyFireCD = 60;
            Character::_enemyFireDamage = 10;
            Character::_enemyFireSpeed = 4;
            Character::_enemyMovementSpeed = 2;
            Character::_enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setFillColor(orange);
            break;

        case 3:
            Character::_playerFireCD = 15;
            Character::_playerFireDamage = 10;
            Character::_playerFireSpeed = 10;
            Character::_playerMovementSpeed = 4;
            Character::_playerInvulCD = 30;
            Character::_enemyFireCD = 40;
            Character::_enemyFireDamage = 15;
            Character::_enemyFireSpeed = 5;
            Character::_enemyMovementSpeed = 2;
            Character::_enemyStandardHP = 40;
            // change difficulty text color
            _difficultyText.setFillColor(sf::Color::Red);
            break;
    }
}

// Voilà, c'est la fin de la classe Game.
// Quelle aventure !.

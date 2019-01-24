#include "Game.hh"
#include <ctime>

// Bonjour ! Bienvenue dans la classe Game, où tout se déroule presque.
// Afin de mieux comprendre comment le jeu fonctionne, veuillez vous
// référencer au "Guide du Stagiaire qui devrait reprendre notre projet",
// ou à aller voir le .h où chaque fonction est expliquée brièvement.
// Nous avons essayé de bien commenter avec de rentre le code simple à
// prendre en main, donc le guide ne sera pas vraiment nécessaire, mais
// (si nous avons le temps de le faire correctement) il y aura peut-être
// des schémas explicatifs de chaque étape du déroulement du jeu.
// Bonne lecture !
//                                  - Victor Verbeke, Dimitri Kokkonis.

// Déclaration des variables statiques (par défaut) des classes du jeu.
// Elles sont déclarées ici pour s'y référencer en allant juste en haut
// du fichier. Character regroupe plein de variables concernant les
// charactéristiques des entités de type "Charactère" (c'est pas pour rien),
// tandis que Textures regroupe l'ensemble des textures utilisées dans le jeu.
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

sf::Texture* Textures::_allyPellet_tex0 = NULL;
sf::Texture* Textures::_allyPellet_tex1 = NULL;
sf::Texture* Textures::_allyPellet_tex2 = NULL;
sf::Texture* Textures::_allyPellet_tex3 = NULL;
sf::Texture* Textures::_allyPellet_tex4 = NULL;
sf::Texture* Textures::_allyPellet_tex5 = NULL;
sf::Texture* Textures::_allyPellet_tex6 = NULL;
sf::Texture* Textures::_allyPellet_tex7 = NULL;
sf::Texture* Textures::_enemyPellet_tex0 = NULL;
sf::Texture* Textures::_enemyPellet_tex1 = NULL;
sf::Texture* Textures::_enemyPellet_tex2 = NULL;
sf::Texture* Textures::_enemyPellet_tex3 = NULL;
sf::Texture* Textures::_enemyPellet_tex4 = NULL;
sf::Texture* Textures::_enemyPellet_tex5 = NULL;
sf::Texture* Textures::_enemyPellet_tex6 = NULL;
sf::Texture* Textures::_enemyPellet_tex7 = NULL;
sf::Texture* Textures::_enemy_tex1 = NULL;
sf::Texture* Textures::_enemy_tex2 = NULL;
sf::Texture* Textures::_enemy_tex3 = NULL;
sf::Texture* Textures::_boss_tex1 = NULL;
sf::Texture* Textures::_boss_tex2 = NULL;
sf::Texture* Textures::_boss_tex3 = NULL;
sf::Texture* Textures::_yun_still_tex = NULL;
sf::Texture* Textures::_yun_hurt_tex = NULL;
sf::Texture* Textures::_yun_hurt_f1_tex = NULL;
sf::Texture* Textures::_panel_lvl1_tex = NULL;
sf::Texture* Textures::_panel_lvl2_tex = NULL;
sf::Texture* Textures::_panel_lvl3_tex = NULL;
sf::Texture* Textures::_background_ingame_tex = NULL;
sf::Texture* Textures::_background_mainMenu_tex = NULL;
sf::Texture* Textures::_background_options_tex = NULL;
sf::Texture* Textures::_background_selectLvl_tex = NULL;
sf::Texture* Textures::_cursor_tex = NULL;


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
    _frameCounter(0),
    _menuSelection(0),
    _difficulty(0),
    _gameState(beginState)
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
    assignationSprites(&_ingameBG_Spr, Textures::_background_ingame_tex, 1620, 1080);
    assignationSprites(&_mainMenuBG_Spr, Textures::_background_mainMenu_tex);
    assignationSprites(&_optionsBG_Spr, Textures::_background_options_tex);
    assignationSprites(&_selectLvlBG_Spr, Textures::_background_selectLvl_tex);
    assignationSprites(&_cursor_Spr, Textures::_cursor_tex, 24, 24);
    assignationSprites(&_panel_Spr, Textures::_panel_lvl1_tex, 390, 290);
    _panel_Spr.setPosition(34, 263);

    // Création des sprites textuels pour le volume et la difficulté.
    stringstream s;
    s << _volume << "%";
    _font.loadFromFile("fonts/OpenSans-Bold.ttf");
    _volumeText.setFont(_font);
    _volumeText.setCharacterSize(50);
    _volumeText.setString(s.str());
    _volumeText.setColor(sf::Color::Yellow);
    _volumeText.setPosition(590, 193);

    _difficultyNames.push_back("Easy");
    _difficultyNames.push_back("Normal");
    _difficultyNames.push_back("Hard");
    _difficultyNames.push_back("YUN.");

    _difficultyText.setFont(_font);
    _difficultyText.setCharacterSize(50);
    _difficultyText.setString(_difficultyNames[_difficulty]);
    _difficultyText.setColor(sf::Color::Yellow);
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
        // case 100 :
        //     // Création de trois ennemis.
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // // Vous avez l'idée.
        // case 500 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 250, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // case 900 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 300, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // case 1000 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 400, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // case 1100 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 300, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // case 1500 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(900, 225, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(900, 350, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(900, 475, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;
        //
        // case 1800 :
        //     addEnemyToVector(Enemy(900, 100, 32, Character::_enemyStandardHP, Textures::_enemy_tex1, wave));
        //     addEnemyToVector(Enemy(950, 225, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(1000, 350, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     addEnemyToVector(Enemy(1050, 475, 32, Character::_enemyStandardHP, Textures::_enemy_tex2, wave));
        //     break;

        case 3 :
            addBossToVector(Boss(Beenzino, Textures::_boss_tex1));
            Game::changeMusic("sounds/musics/beenzino.ogg");
        // Si y'a rien, alors il ne se passe rien. Logique.
        default :
            break;
    }
}

// Fonction d'attaque de chaque ennemi.
// Pour chaque ennemi dans le vecteur d'ennemi, on appelle la fonction fire().
// L'ennemi tire vers le joueur. Puis ensuite, on réduit le cooldown pour
// éviter qu'il tire en continu.
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
    // Yun va bouger : ces deux variables correspondent à ses déplacements.
    // Selon les flags, ils vont être modifiés, donc on peut considérer que
    // ce sont plus des dx et dy que x et y, mais peu importe.
// supprime tous les pellets touchés. Sinon, il prend des dégats de la part
// des ennemis ou des pellets.
void Game::checkYunCollisions(){
    if (yun.getInvulCD() == 0)
    {
        checkYunCollisionsEnemies();
        checkYunCollisionsPellets(true);

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
        yun.setInvulCD(yun.getInvulCD() - 1); // On réduit le temps
        if (yun.getIsHurt() == true){   // d'invincibilité. Si il s'agit de la
            yun.setIsHurt(false);   // deuxième frame d'invincibilité, alors on
        // modifie la texture pour indiquer qu'il est blessé. La première frame
        // est un Yun rouge, pour montrer la frame où il est blessé (check
        // l'overload de Player pour ça.)
            yun._sprite.setTexture(*(Textures::_yun_hurt_tex));
        }
        // A la dernière frame, on remet Yun tranquille content.
        if (yun.getInvulCD() == 0){
            yun._sprite.setTexture(*(Textures::_yun_still_tex));
        }
        checkYunCollisionsPellets(false);
    }
    // TODO : La collision avec les powerups.
    checkYunCollisionsPowerUp();
}

// Yun touche un ennemi = Il prend des dégats (si il est pas invulnérable).
// Ici, on parcourt le vecteur d'ennemis et on invoque la surcharge - de Player
// pour lui infliger des dégats.
void Game::checkYunCollisionsEnemies(){
    // Si yun n'est pas invulnérable, il prend des dégats des ennemis.
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); itEnemy++){
        if (yun._hitbox.getGlobalBounds().intersects((*itEnemy)._hitbox.getGlobalBounds()))
        {
            yun - (Character::_enemyFireDamage * 2);
        }
    }

    // Au passage, il prend la même chose de la part des boss.
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

    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); )
    {
        if ((*itPellet)._target == 0) // Si les pellets visent Yun
        {
            if (yun._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds()))
            {
                if (vulnerable) yun - (*itPellet)._damage;  // Il prend des dégats
                itPellet = pelletVector.erase(itPellet); // On supprime le pellet.
            } else itPellet++;
        } else itPellet++;
    }
}

// Si Yun touche un powerup, il est amélioré durant TOUTE la partie.
void Game::checkYunCollisionsPowerUp(){} // TODO

// Si un ennemi rencontre un pellet tiré par le joueur, alors il est blessé.
// Pour la mort de l'ennemi, voir la surcharge de l'opérateur - dans Enemy.
void Game::checkEnemyCollisions(){
    bool enemyKilled = false;
    // Les ennemis ne sont blessés que par les pellets tirés par Yun
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        enemyKilled = false;
        vector<Pellet>::iterator itPellet = pelletVector.begin();
        for ( ; itPellet != pelletVector.end(); ){
            if (enemyKilled == false){
                if ((*itPellet)._target == 1){
                    if ((*itEnemy)._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds())){
                        (*itEnemy) - (*itPellet)._damage;
                        itPellet = pelletVector.erase(itPellet);
                        if ((*itEnemy).getHp() <= 0) enemyKilled = true;
                    } else itPellet++;
                } else itPellet++;
            } else itPellet++;
        }

        if (enemyKilled == false) itEnemy++;
        else {

            itEnemy = enemyVector.erase(itEnemy);
            playRandomKillSound(); // Enemy killed, play a victory sound
            // addPowerUpToVector(new PowerUp()); // TODO POWERUPS TODO TODO
        }
    }
}

void Game::checkBossCollisions(){
    bool isKilled = false;
    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); ){
        isKilled = false;
        vector<Pellet>::iterator itPellet = pelletVector.begin();
        for ( ; itPellet != pelletVector.end(); ){
            if (isKilled == false){
                if ((*itPellet)._target == 1){
                    if ((*itBoss)._hitbox.getGlobalBounds().intersects((*itPellet)._hitbox.getGlobalBounds())){
                        (*itBoss) - (*itPellet)._damage;
                        itPellet = pelletVector.erase(itPellet);
                        if ((*itBoss).getHp() <= 0) isKilled = true;
                    } else itPellet++;
                } else itPellet++;
            } else itPellet++;
        }

        if (isKilled == false) itBoss++;
        else {
            itBoss = bossVector.erase(itBoss);
            playRandomKillSound(); // Enemy killed, play a victory sound
            // addPowerUpToVector(new PowerUp()); // TODO POWERUPS TODO TODO
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
// Toutes les classes possèdent un moyen de se déplacer : Yun manuellement (x,y)
// et les autres ont une vitesse et une direction. A chaque frame, on fait
// bouger les entités avec les fonctions suivantes.

// moveYun permet de... bouger Yun. C'est grâce aux flags dans les Events.
void Game::moveYun(){

    // Yun va bouger : ces deux variables correspondent à ses déplacements.
    // Selon les flags, ils vont être modifiés, donc on peut considérer que
    // ce sont plus des dx et dy que x et y, mais peu importe.
    x = 0;
    y = 0;

    // Si on appuie sur gauche et qu'on est pas sur le rebord gauche, alors
    // on peut bouger vers la gauche. Même idée pour les quatre directions.
    if (leftFlag && (yun._x - yun._size/2) > 0) x -= Character::_playerMovementSpeed;
    if (rightFlag && (yun._x - yun._size/2) < getSize().x - yun._size) x += Character::_playerMovementSpeed;
    if (upFlag && (yun._y - yun._size/2) > 0) y -= Character::_playerMovementSpeed;
    if (downFlag && (yun._y - yun._size/2) < getSize().y - yun._size) y += Character::_playerMovementSpeed;

    if (shiftFlag){     // Si on appuie sur Shift, on peut naviguer plus
        x = x/2;        // lentement. Utile lors des situations délicates où
        y = y/2;        // on doit naviguer entre les balles.
    }
    yun.move(x, y);
    yun.decreaseCD();
                            // moveEntity viendra plus tard, mais ça permet de
                            // faire bouger une entité.
           // Comme la fonction moveYun est appelée à chaque
                            // frame, on en profite pour faire réduire son
                            // cooldown d'attaque ici.
}

// Somme de toutes les méthodes de déplacement d'entités.
void Game::moveEntities(){
    moveYun();

    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        if ((*itEnemy)._x < -(*itEnemy)._size || (*itEnemy)._y < -(*itEnemy)._size || (*itEnemy)._y > getSize().y){
            itEnemy = enemyVector.erase(itEnemy);
        } else {
            (*itEnemy).move();
            itEnemy++;
        }
    }

    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); ){
        if ((*itPellet)._x < 0 || (*itPellet)._x > getSize().x || (*itPellet)._y < 0 || (*itPellet)._y > getSize().y){
            itPellet = pelletVector.erase(itPellet);
        } else {
            (*itPellet).move();
            itPellet++;
        }
    }

    vector<PowerUp>::iterator itPowerUp = pUpVector.begin();
    for ( ; itPowerUp != pUpVector.end(); ){
        if ((*itPowerUp)._x < 0 || (*itPowerUp)._x > getSize().x || (*itPowerUp)._y < 0 || (*itPowerUp)._y > getSize().y){
            itPowerUp = pUpVector.erase(itPowerUp);
        } else {
            (*itPowerUp).move();
            itPowerUp++;
        }
    }

    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); ){
        if ((*itBoss)._x < 0 || (*itBoss)._x > getSize().x || (*itBoss)._y < 0 || (*itBoss)._y > getSize().y){
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
    display();
}

// Selon l'état du jeu et la sélection du menu (le bouton visé), on
// déplace le curseur à l'écran. Toutes les valeurs sont faites à la main.
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

        default: // On le sort de l'écran.
            _cursor_Spr.setPosition(-100, -100);
            break;
    }
    draw(_cursor_Spr);
}

// Methodes d'affichage Ingame !

// On veut que le background défile en fond.
// On fait donc en sorte que l'image soit basée sur le temps passé en jeu.
void Game::drawBackground(){
    draw(_ingameBG_Spr);
    _ingameBG_Spr.setPosition(-0.1*_frameCounter, 0);
}

// Méthode d'appel des différentes méthodes d'affichage des entités.
void Game::drawEntities(){

    // Draw every Pellet, Enemy, Boss and PowerUp (weird flex but ok)
    for(vector<Enemy>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++)
        drawEntity((*it));
    for(vector<Boss>::iterator it = bossVector.begin(); it != bossVector.end(); it++)
        drawEntity((*it));
    for(vector<PowerUp>::iterator it = pUpVector.begin(); it != pUpVector.end(); it++)
        drawEntity((*it));
    for(vector<Pellet>::iterator it = pelletVector.begin(); it != pelletVector.end(); it++)
        drawEntity((*it));
    // Draw the Player after everything.
    drawEntity(yun);
}


// Methodes d'ajout d'entités dans les vecteurs de la classe Game.
// Généralement on fait addXToVector(new X(args)).
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
// Les vecteurs, etc... selon l'état actuel et le suivant.
void Game::changeState(State nextState){
    _frameCounter = 0;
    _menuSelection = 0;
    yun.setHp(100);
    switch (nextState){
        case level1 :
        case level2 :
        case level3 :
            enemyVector.clear();
            pelletVector.clear();
            pUpVector.clear();
            bossVector.clear();
            yun._x = 100;
            yun._y = 274;
            if ((_gameState == mainMenu) || (_gameState == selectLvl))
                changeMusic("sounds/musics/battle_music.ogg");
            _gameState = nextState;
            break;

        case selectLvl :
            _selectedLevel = level1; // Petit hack pour toujours afficher le
            changeLevel(1);     // premier niveau en arrivant sur le menu :
            changeLevel(-1);    // mettre au niveau 1, avancer puis reculer pour
                                // mettre à jour l'affichage.
        case mainMenu :
        case options :
            if ((_gameState == beginState) || (_gameState == level3) || (_gameState == level2) || (_gameState == level1))
                changeMusic("sounds/musics/main_menu_music.ogg");
            _gameState = nextState;
            break;

        default:
            break;
    }
}

// Cette méthode permet de changer de musique. Le musicPath est le chemin
// du fichier à lire.
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
                _panel_Spr.setTexture(*(Textures::_panel_lvl2_tex));
                _selectedLevel = level2;
            }

            break;

        case level2 :
            if (i > 0) {
                _panel_Spr.setTexture(*(Textures::_panel_lvl3_tex));
                _selectedLevel = level3;
            }
            if (i < 0) {
                _panel_Spr.setTexture(*(Textures::_panel_lvl1_tex));
                _selectedLevel = level1;
            }
            break;

        case level3 :
            if (i < 0) {
                _panel_Spr.setTexture(*(Textures::_panel_lvl2_tex));
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
        if (_volume < 100) _volume += 5;
    }
    else if (i < 0){
        if (_volume > 0) _volume -= 5;
    }

    stringstream s;

    s << _volume << "%";
    _playerKillSound.setVolume(_volume);
    _playerDamageSound.setVolume(_volume);
    _music.setVolume(_volume);
    _volumeText.setString(s.str());
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
            _difficultyText.setColor(sf::Color::Green);
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
            _difficultyText.setColor(sf::Color::Yellow);
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
            _difficultyText.setColor(orange);
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
            _difficultyText.setColor(sf::Color::Red);
            break;
    }
}

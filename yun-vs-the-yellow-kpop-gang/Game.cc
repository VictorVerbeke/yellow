#include "Game.hh"
#include <ctime>

// Déclaration nécessaire pour fonctionner des
// éléments statiques de Character.
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

Game::Game(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name),
    _frameCounter(0),
    _menuSelection(0),
    _difficulty(0),
    _gameState(beginState)
{
    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);
    _music.setLoop(true);
    _volume = 100;
    // Assignations des valeurs de base aux Attributs : Flags
    upFlag = false;
    downFlag = false;
    rightFlag = false;
    leftFlag = false;
    shiftFlag = false;
    firingFlag = false;

    // Création des Sprites
    assignationSprites(&_ingameBG_Spr, Textures::_background_ingame_tex, 1620, 1080);
    assignationSprites(&_mainMenuBG_Spr, Textures::_background_mainMenu_tex);
    assignationSprites(&_optionsBG_Spr, Textures::_background_options_tex);
    assignationSprites(&_selectLvlBG_Spr, Textures::_background_selectLvl_tex);
    assignationSprites(&_cursor_Spr, Textures::_cursor_tex, 24, 24);
    assignationSprites(&_panel_Spr, Textures::_panel_lvl1_tex, 390, 290);
    _panel_Spr.setPosition(34, 263);

    // Text labels for volume & difficulty
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


    // PLAYER SOUND BUFFERS
    _bufferDamage1.loadFromFile("sounds/yun_phrases/damage_1.ogg");
    _bufferDamage2.loadFromFile("sounds/yun_phrases/damage_2.ogg");

    _bufferKill1.loadFromFile("sounds/yun_phrases/oui.ogg");
    _bufferKill2.loadFromFile("sounds/yun_phrases/protocole_rip_1.ogg");
    _bufferKill3.loadFromFile("sounds/yun_phrases/protocole_rip_2.ogg");
    _bufferKill4.loadFromFile("sounds/yun_phrases/RIP.ogg");
    _bufferKill5.loadFromFile("sounds/yun_phrases/seine.ogg");
}

void Game::assignationSprites(sf::Sprite *spr, sf::Texture *tex, int x, int y){

    spr->setTexture(*tex);
    spr->setTextureRect(sf::IntRect(0, 0, x, y));
    spr->setPosition(0,0);
    spr->setTexture(*tex);
}

Game::~Game(){
}

// Methode principale : Là où se déroule tout le jeu, beginGame().
void Game::beginGame(){
    changeState(mainMenu);
    setDifficulty(1);
    // Run the program as long as the window is open
    while (isOpen())
    {
        switch (_gameState){
            case mainMenu:
                checkEventMainMenu();
                drawMainMenu();
                break;
            case options:
                checkEventOptions();
                drawOptions();
                break;
            case selectLvl:
                checkEventSelectLvl();
                drawSelectLvl();
                break;
            case level1:
                checkEventIngame();
                scriptedEvents();
                moveEntities();
                checkAllCollisions();
                drawIngame();
                enemyAttack();
                break;
            default :
                changeState(mainMenu);
                break;
        }
    }
}

void Game::scriptedEvents(){

    _frameCounter++;
    switch (_frameCounter){
        case 100 : {
            Enemy* enemy1 = new Enemy(900, 100, 32, yun._enemyStandardHP, Textures::_enemy_tex1, wave);
            Enemy* enemy2 = new Enemy(900, 250, 32, yun._enemyStandardHP, Textures::_enemy_tex2, wave);
            Enemy* enemy3 = new Enemy(900, 400, 32, yun._enemyStandardHP, Textures::_enemy_tex3, wave);
            addEnemyToVector(enemy1);
            addEnemyToVector(enemy2);
            addEnemyToVector(enemy3);
            break;
        }

        case 500 : {
            Enemy* enemy4 = new Enemy(900, 100, 32, yun._enemyStandardHP, Textures::_enemy_tex1, wave);
            Enemy* enemy5 = new Enemy(900, 250, 32, yun._enemyStandardHP, Textures::_enemy_tex2, wave);
            Enemy* enemy6 = new Enemy(900, 400, 32, yun._enemyStandardHP, Textures::_enemy_tex3, wave);
            addEnemyToVector(enemy4);
            addEnemyToVector(enemy5);
            addEnemyToVector(enemy6);
            break;
        }

        default :
            break;
    }
}

void Game::enemyAttack(){
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); itEnemy++){
        addPelletToVector((&(*itEnemy))->fire(yun._sprite.getPosition()));
        (&(*itEnemy))->decreaseCD();
    }
}

void Game::goMenuSelection(int sel){
    switch(_gameState){
        case mainMenu :
            if (sel == 0) changeState(level1);      // Bouton "New Game"
            else if (sel == 1) changeState(selectLvl);   // Bouton "Level Select"
            else if (sel == 2) changeState(options);     // Bouton "Options"
            else if (sel == 3) this->close();                  // Bouton "Exit Game"
            break;

        case selectLvl:
            if (sel == 0) changeState(_selectedLevel);
            else if (sel == 1) changeState(mainMenu);// Bouton "Back to main menu"
            break;

        case options:
            if (sel == 2) changeState(mainMenu);// Bouton "Back to main menu"
            // Les autres boutons n'en sont pas, ils modifient des valeurs.
            break;
        default:
            break;
    }
}


// Gestion des events.
void Game::checkEventMainMenu(){

    sf::Event event;
    while(pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                close();
                break;

            case sf::Event::KeyPressed:         // Ci-dessous : Equivaut à (x-1) % 4 mais ca marche pas bizarrement.
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

void Game::checkEventOptions(){

    sf::Event event;
    while(pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up) _menuSelection = (_menuSelection + 2) % 3;
                else if (event.key.code == sf::Keyboard::Down) _menuSelection = (_menuSelection + 1)%3;
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (_menuSelection == 0) setVolume(-1);     // Baisser le volume
                    else if (_menuSelection == 1) setDifficulty(-1); // Baisser la difficulté
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (_menuSelection == 0) setVolume(1);      // Augmenter le volume
                    else if (_menuSelection == 1) setDifficulty(1);  // Augmenter la difficulté
                }
                else if (event.key.code == sf::Keyboard::Return) goMenuSelection(_menuSelection);
                else if (event.key.code == sf::Keyboard::Space) goMenuSelection(_menuSelection);
                else if (event.key.code == sf::Keyboard::Escape) changeState(mainMenu);
                break;

            default:
                break;
        }
    }
}

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

    x = 0;
    y = 0;
    sf::Event event;

    while (pollEvent(event))
    {
        switch (event.type) {
                case sf::Event::Closed:
                // "close requested" event: we close the window
                close();
                break;

            case sf::Event::KeyPressed:
                // Process the up, down, left and right keys
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
    if (firingFlag) addPelletToVector(yun.fire());
}


// Methodes de collision
void Game::checkYunCollisions(){
    if (yun._invulCD == 0)
    {
        checkYunCollisionsEnemies();
        checkYunCollisionsPellets(true);

        if (rand() > RAND_MAX / 2)
            _playerDamageSound.setBuffer(_bufferDamage1);
        else
            _playerDamageSound.setBuffer(_bufferDamage2);
        _playerDamageSound.play();
    }
    else
    {
        yun._invulCD--;
        if (yun._isHurt == true){
            yun._isHurt = false;
            yun._sprite.setTexture(*(Textures::_yun_hurt_tex));
        }
        if (yun._invulCD == 0){
            yun._sprite.setTexture(*(Textures::_yun_still_tex));
        }
        checkYunCollisionsPellets(false);
    }
    checkYunCollisionsPowerUp();
}

void Game::checkYunCollisionsEnemies(){
    // Si yun n'est pas invulnérable, il prend des dégats des ennemis.
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); itEnemy++){
        if (yun._sprite.getGlobalBounds().intersects((&(*itEnemy))->_sprite.getGlobalBounds())){;
            yun - 10;
        }
    }
}

void Game::checkYunCollisionsPellets(bool vulnerable){

    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); )
    {
        if ((&(*itPellet))->_target == 0) // Si les pellets visent Yun
        {
            if (yun._sprite.getGlobalBounds().intersects((&(*itPellet))->_sprite.getGlobalBounds()))
            {
                if (vulnerable) yun - (&(*itPellet))->_damage;  // Il prend des dégats
                itPellet = pelletVector.erase(itPellet); // On supprime le pellet.
            } else itPellet++;
        } else itPellet++;
    }
}

void Game::checkYunCollisionsPowerUp(){} // TODO

void Game::checkEnemyCollisions(){
    bool enemyKilled = false;
    // Les ennemis ne sont blessés que par les pellets tirés par Yun
    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        enemyKilled = false;
        vector<Pellet>::iterator itPellet = pelletVector.begin();
        for ( ; itPellet != pelletVector.end(); ){
            if (enemyKilled == false){
                if ((&(*itPellet))->_target == 1){
                    if ((&(*itEnemy))->_sprite.getGlobalBounds().intersects((&(*itPellet))->_sprite.getGlobalBounds())){
                        (*itEnemy) - (&(*itPellet))->_damage;
                        itPellet = pelletVector.erase(itPellet);
                        if ((&(*itEnemy))->getHp() <= 0) enemyKilled = true;
                    } else itPellet++;
                } else itPellet++;
            } else itPellet++;
        }

        if (enemyKilled == false) itEnemy++;
        else {
            itEnemy = enemyVector.erase(itEnemy);

            // Enemy killed, play a victory sound

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
    }
}

void Game::checkAllCollisions(){

    checkYunCollisions();
    checkEnemyCollisions();


}


// Methodes de déplacementgoMe
void Game::moveYun(){
    // Update coordinates
    x = 0;
    y = 0;
    if (leftFlag && yun._x > 0) x -= yun._playerMovementSpeed;
    if (rightFlag && yun._x < getSize().x - yun._size) x += yun._playerMovementSpeed;
    if (upFlag && yun._y > 0) y -= yun._playerMovementSpeed;
    if (downFlag && yun._y < getSize().y - yun._size) y += yun._playerMovementSpeed;
    if (shiftFlag){
        x = x/2;
        y = y/2;
    }
    moveEntity(&yun, x, y);
    yun.decreaseCD();
}

void Game::moveEntity(Player *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);

}

void Game::moveEntity(Enemy *object){
    switch (object->_pattern){
        case line:
            object->_x += object->_speed * sin(object->_direction * PI /180);
            object->_y += object->_speed * cos(object->_direction * PI /180);
            break;

        case wave:
            object->_x += object->_speed * sin(object->_direction * PI / 180);
            object->_y += object->_speed * cos(object->_direction * PI / 180);
            if (object->_direction >= -45) object->_directionVariation = -1;
            if (object->_direction <= -135) object->_directionVariation = 1;
            object->_direction += object->_directionVariation;
            break;

        case still:
        default:
            break;
    }
    object->_sprite.setPosition(object->_x, object->_y);
}

void Game::moveEntity(Boss *object){
    switch (object->_pattern){
        case line:
        object->_x += object->_speed * sin(object->_direction * PI /180);
        object->_y += object->_speed * cos(object->_direction * PI /180);
            break;

        case wave:
            object->_x += object->_speed * sin(object->_direction * PI / 180);
            object->_y += object->_speed * cos(object->_direction * PI / 180);
            if (object->_direction >= 315) object->_directionVariation = -1;
            if (object->_direction <= 225) object->_directionVariation = 1;
            object->_direction += object->_directionVariation;
            break;

        case still:
        default:
            break;
    }
    object->_sprite.setPosition(object->_x, object->_y);
}

void Game::moveEntity(Pellet *object){
    object->_x += (object->_speed) * cos(object->_direction * PI / 180);
    object->_y += (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);
    object->_frameCounter++;
    if (object->_frameCounter == 3) object->nextFrame();

}

void Game::moveEntity(PowerUp *object){
    object->_x += (object->_speed) * cos(object->_direction * PI / 180);
    object->_y += (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);

}

void Game::moveEntities(){
    moveYun();

    vector<Enemy>::iterator itEnemy = enemyVector.begin();
    for ( ; itEnemy != enemyVector.end(); ){
        if ((&(*itEnemy))->_x < -(&(*itEnemy))->_size || (&(*itEnemy))->_y < -(&(*itEnemy))->_size || (&(*itEnemy))->_y > getSize().y){
            itEnemy = enemyVector.erase(itEnemy);
        } else {
            moveEntity(&(*itEnemy));
            itEnemy++;
        }
    }

    vector<Pellet>::iterator itPellet = pelletVector.begin();
    for ( ; itPellet != pelletVector.end(); ){
        if ((&(*itPellet))->_x < 0 || (&(*itPellet))->_x > getSize().x || (&(*itPellet))->_y < 0 || (&(*itPellet))->_y > getSize().y){
            itPellet = pelletVector.erase(itPellet);
        } else {
            moveEntity(&(*itPellet));
            itPellet++;
        }
    }

    vector<PowerUp>::iterator itPowerUp = pUpVector.begin();
    for ( ; itPowerUp != pUpVector.end(); ){
        if ((&(*itPowerUp))->_x < 0 || (&(*itPowerUp))->_x > getSize().x || (&(*itPowerUp))->_y < 0 || (&(*itPowerUp))->_y > getSize().y){
            itPowerUp = pUpVector.erase(itPowerUp);
        } else {
            moveEntity(&(*itPowerUp));
            itPowerUp++;
        }
    }

    vector<Boss>::iterator itBoss = bossVector.begin();
    for ( ; itBoss != bossVector.end(); ){
        if ((&(*itBoss))->_x < 0 || (&(*itBoss))->_x > getSize().x || (&(*itBoss))->_y < 0 || (&(*itBoss))->_y > getSize().y){
            itBoss = bossVector.erase(itBoss);
        } else {
            moveEntity(&(*itBoss));
            itBoss++;
        }
    }

}


// Methodes d'affichage générales
void Game::drawMainMenu(){
    clear(sf::Color(0,127,0));
    draw(_mainMenuBG_Spr);
    drawCursor();
    display();
}

void Game::drawOptions(){
    clear(sf::Color(127,0,0));
    draw(_optionsBG_Spr);
    draw(_volumeText);
    draw(_difficultyText);
    drawCursor();
    display();
}

void Game::drawSelectLvl(){
    clear(sf::Color(0,0,127));
    draw(_selectLvlBG_Spr);
    draw(_panel_Spr);
    drawCursor();
    display();
}

void Game::drawIngame(){
    // Clear the window and apply grey background
    clear(sf::Color(0,0,0));
    drawBackground();
    drawEntities();
    display();
}

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

// Methodes d'affichage Ingame
void Game::drawBackground(){
    draw(_ingameBG_Spr);
    _ingameBG_Spr.setPosition(-0.1*_frameCounter, 0);
}

// void Game::drawEntity(Player* object){
//     draw(object->_sprite);
//     // On en profite : on réduit le cooldown de tir à chaque frame
//     object->decreaseCD();
// }
//
// void Game::drawEntity(Boss *object){
//     draw(object->_sprite);
// }
//
// void Game::drawEntity(Enemy *object){
//     draw(object->_sprite);
// }
//
// void Game::drawEntity(PowerUp *object){
//     draw(object->_sprite);
// }
//
// void Game::drawEntity(Pellet *object){
//     draw(object->_sprite);
// }

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


// Methodes d'ajout d'instances
void Game::addPelletToVector(Pellet* object){
    if (object != NULL) pelletVector.push_back(*object);

}

void Game::addEnemyToVector(Enemy* object){
    if (object != NULL) enemyVector.push_back(*object);
}

void Game::addPowerUpToVector(PowerUp* object){
    if (object != NULL) pUpVector.push_back(*object);
}

void Game::addBossToVector(Boss* object){
    if (object != NULL) bossVector.push_back(*object);
}

// Gestion    _gameState;
void Game::changeState(State nextState){
    _frameCounter = 0;
    _menuSelection = 0;
    yun.setHp(100);
    switch (nextState){
        case level1 :
        case level2 :
        case level3 :
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

void Game::changeMusic(string musicPath){

    _music.pause();
    if (!_music.openFromFile(musicPath)){
        cerr << "Failed to open music : " << musicPath << endl;
        exit(1);
    }
    _music.play();
}

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

void Game::setVolume(int i){
    if (i > 0){
        if (_volume < 100) _volume += 5;
    }
    else if (i < 0){
        if (_volume > 0) _volume -= 5;
    }

    stringstream s;

    s << _volume << "%";

    _music.setVolume(_volume);
    _volumeText.setString(s.str());
}

void Game::setDifficulty(int i){
    // La difficulté va de 0 (easy) à 3 (yun, soit very hard)
    if (i > 0) if (_difficulty < 3) _difficulty++;
    if (i < 0) if (_difficulty > 0) _difficulty--;
    modifyDifficulty();
    _difficultyText.setString(_difficultyNames[_difficulty]);
}

void Game::modifyDifficulty(){

    // To change the color of the difficulty text
    sf::Color orange(255, 132, 26, 255);

    switch (_difficulty)
    {
        case 0 :
            yun._playerFireCD = 15;
            yun._playerFireDamage = 50;
            yun._playerFireSpeed = 10;
            yun._playerMovementSpeed = 4;
            yun._playerInvulCD = 100;
            yun._enemyFireCD = 120;
            yun._enemyFireDamage = 5;
            yun._enemyFireSpeed = 2;
            yun._enemyMovementSpeed = 2;
            yun._enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setColor(sf::Color::Green);
            break;

        case 1 :
            yun._playerFireCD = 15;
            yun._playerFireDamage = 20;
            yun._playerFireSpeed = 10;
            yun._playerMovementSpeed = 4;
            yun._playerInvulCD = 60;
            yun._enemyFireCD = 80;
            yun._enemyFireDamage = 5;
            yun._enemyFireSpeed = 3;
            yun._enemyMovementSpeed = 2;
            yun._enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setColor(sf::Color::Yellow);
            break;

        case 2 :
            yun._playerFireCD = 15;
            yun._playerFireDamage = 15;
            yun._playerFireSpeed = 10;
            yun._playerMovementSpeed = 4;
            yun._playerInvulCD = 40;
            yun._enemyFireCD = 60;
            yun._enemyFireDamage = 10;
            yun._enemyFireSpeed = 4;
            yun._enemyMovementSpeed = 2;
            yun._enemyStandardHP = 30;
            // change difficulty text color
            _difficultyText.setColor(orange);
            break;

        case 3:
            yun._playerFireCD = 15;
            yun._playerFireDamage = 10;
            yun._playerFireSpeed = 10;
            yun._playerMovementSpeed = 4;
            yun._playerInvulCD = 30;
            yun._enemyFireCD = 40;
            yun._enemyFireDamage = 15;
            yun._enemyFireSpeed = 5;
            yun._enemyMovementSpeed = 2;
            yun._enemyStandardHP = 40;
            // change difficulty text color
            _difficultyText.setColor(sf::Color::Red);
            break;
    }
}

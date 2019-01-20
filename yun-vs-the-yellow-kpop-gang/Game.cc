#include "Game.hh"

Game::Game(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name)
{

    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);

    // Assignations des valeurs de base aux Attributs : Flags
    upFlag = false;
    downFlag = false;
    rightFlag = false;
    leftFlag = false;
    shiftFlag = false;
    firingFlag = false;

    // Autres assignations
    _frameCounter = 0;
}

Game::~Game(){
}

// Methode principale : Là où se déroule tout le jeu, beginGame().
void Game::beginGame(){

    // Run the program as long as the window is open
    while (isOpen())
    {
        checkEvent();
        scriptedEvents();
        moveEntities();
        checkCollisions();
        refreshDisplay();
        cout << yun.getHp() << ", " << _frameCounter << endl << endl;
        _frameCounter++;
    }
}

void Game::checkEvent(){

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
                if (event.key.code == sf::Keyboard::Escape) close();
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

void Game::scriptedEvents(){
    switch (_frameCounter){
        case 100 : {
            cout << "Bon. ";
            Enemy* enemy1 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            Enemy* enemy2 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            Enemy* enemy3 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            cout << "Check 1... ";
            enemy1->_x = 1000; enemy1->_y = 100;
            enemy2->_x = 1000; enemy2->_y = 250;
            enemy3->_x = 1000; enemy3->_y = 400;
            cout << "2... ";
            addEnemyToVector(enemy1);
            addEnemyToVector(enemy2);
            addEnemyToVector(enemy3); cout << "5 !" << endl;
            break;
        }

        case 1000 : {
            Enemy* enemy4 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            Enemy* enemy5 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            Enemy* enemy6 = new Enemy(0, 0, 48, 50, "images/minion_48.png", wave);
            enemy4->_x = 1000; enemy4->_y = 100;
            enemy5->_x = 1000; enemy5->_y = 250;
            enemy6->_x = 1000; enemy6->_y = 400;
            addEnemyToVector(enemy4);
            addEnemyToVector(enemy5);
            addEnemyToVector(enemy6);
            break;
        }

        default :
            break;
    }
}

void Game::refreshDisplay(){
    // Clear the window and apply grey background
    clear(sf::Color(127,127,127));
    drawEntities();
    display();
}

void Game::checkCollisions(){

    // Le joueur ne doit toucher ni les balles, ni les ennemis
    vector<Enemy>::iterator it = enemyVector.begin();
    for ( ; it != enemyVector.end(); it++){
        if (yun._sprite.getGlobalBounds().intersects((&(*it))->_sprite.getGlobalBounds())){;
            yun - 10;
        }
    }
}


// Methodes de déplacement
void Game::moveYun(){
    // Update coordinates
    x = 0;
    y = 0;
    if (leftFlag && yun._x > 0) x -= PLAYER_SPEED;
    if (rightFlag && yun._x < getSize().x - yun._size) x += PLAYER_SPEED;
    if (upFlag && yun._y > 0) y -= PLAYER_SPEED;
    if (downFlag && yun._y < getSize().y - yun._size) y += PLAYER_SPEED;
    if (shiftFlag){
        x = x/2;
        y = y/2;
    }
    moveEntity(&yun, x, y);
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


// Methodes d'affichage
void Game::drawEntity(Player* object){
    draw(object->_sprite);
    // On en profite : on réduit le cooldown de tir à chaque frame
    object->decreaseCD();
}

void Game::drawEntity(Boss *object){
    draw(object->_sprite);
}

void Game::drawEntity(Enemy *object){
    draw(object->_sprite);
}

void Game::drawEntity(PowerUp *object){
    draw(object->_sprite);
}

void Game::drawEntity(Pellet *object){
    draw(object->_sprite);
}

void Game::drawEntities(){

    // Draw every Pellet, Enemy, Boss and PowerUp (weird flex but ok)
    for(vector<Enemy>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++)
        drawEntity(&(*it));
    for(vector<Boss>::iterator it = bossVector.begin(); it != bossVector.end(); it++)
        drawEntity(&(*it));
    for(vector<PowerUp>::iterator it = pUpVector.begin(); it != pUpVector.end(); it++)
        drawEntity(&(*it));
    for(vector<Pellet>::iterator it = pelletVector.begin(); it != pelletVector.end(); it++)
        drawEntity(&(*it));
    // Draw the Player after everything.
    drawEntity(&yun);
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

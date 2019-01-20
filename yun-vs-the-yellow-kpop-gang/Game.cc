#include "Game.hh"

Player yun_template(0, 0, 100, "images/yun_test_100.png");

Game::Game(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name)
{

    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);

    // Assignations des valeurs de base aux Attributs
    upFlag = false;
    downFlag = false;
    rightFlag = false;
    leftFlag = false;
    shiftFlag = false;

    x = 0;
    y = 0;
}

Game::~Game(){
    delete(this);
}

// Methode principale : Là où se déroule tout le jeu, beginGame().
void Game::beginGame(){

    // Run the program as long as the window is open
    while (isOpen())
    {
        checkEvent();
        moveYun();
        refreshDisplay();

    }
}

void Game::checkEvent(){

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
                if (event.key.code == sf::Keyboard::Space) yun.fire();
                if (event.key.code == sf::Keyboard::Escape) close();
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) upFlag = false;
                if (event.key.code == sf::Keyboard::Down) downFlag = false;
                if (event.key.code == sf::Keyboard::Left) leftFlag = false;
                if (event.key.code == sf::Keyboard::Right) rightFlag = false;
                if (event.key.code == sf::Keyboard::LShift) shiftFlag = false;
                break;

            default:
                break;
        }
    }
}

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

void Game::refreshDisplay(){
    // Clear the window and apply grey background
    clear(sf::Color(127,127,127));

    // Draw every Pellet, Enemy, Boss and PowerUp (weird flex but ok)
    for(vector<Pellet>::iterator it = pelletVector.begin(); it != pelletVector.end(); it++)
        drawEntity(&(*it));
    for(vector<Enemy>::iterator it = enemyVector.begin(); it != enemyVector.end(); it++)
        drawEntity(&(*it));
    for(vector<Boss>::iterator it = bossVector.begin(); it != bossVector.end(); it++)
        drawEntity(&(*it));
    for(vector<PowerUp>::iterator it = pUpVector.begin(); it != pUpVector.end(); it++)
        drawEntity(&(*it));

    // Draw the Player
    drawEntity(&yun);

    // end the current frame
    display();
}


// Methodes de déplacement
void Game::moveEntity(Player *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);

}

void Game::moveEntity(Enemy *object){
    switch (object->_pattern){
        case line:
            object->_x += object->_speed;
            break;

        case wave:
            object->_x += object->_speed * sin(object->_direction);
            object->_y += object->_speed * cos(object->_direction);
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

void Game::moveEntity(Boss *object){
    switch (object->_pattern){
        case line:
            object->_x += object->_speed;
            break;

        case wave:
            object->_x += object->_speed * sin(object->_direction);
            object->_y += object->_speed * cos(object->_direction);
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
    object->_x = object->_x + (object->_speed) * cos(object->_direction * PI / 180);
    object->_y = object->_y + (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);
}

void Game::moveEntity(PowerUp *object){
    object->_x = object->_x + (object->_speed) * cos(object->_direction * PI / 180);
    object->_y = object->_y + (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);
}

// Methodes d'affichage
void Game::drawEntity(Player* object){
    draw(object->_sprite);
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

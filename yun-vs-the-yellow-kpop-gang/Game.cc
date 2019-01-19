#include "Game.hh"
#define PI 3.141592653

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

    x = 0;
    y = 0;
    yun = new Player(0, 0, 100, "images/yun_test_100.png");
}

Game::~Game(){
    delete(this);
}

// Methode principale : Là où se déroule tout le jeu, beginGame().
void Game::beginGame(){

    // Run the program as long as the window is open
    while (game.isOpen())
    {
        game.checkEvent();
        game.moveYun();
        game.refreshDisplay();

    }
}

void Game::checkEvent(){

    sf::Event event;
    while (game.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                game.close();
                break;

            case sf::Event::KeyPressed:
                // Process the up, down, left and right keys
                if (event.key.code == sf::Keyboard::Up) upFlag = true;
                if (event.key.code == sf::Keyboard::Down) downFlag = true;
                if (event.key.code == sf::Keyboard::Left) leftFlag = true;
                if (event.key.code == sf::Keyboard::Right) rightFlag = true;
                if (event.key.code == sf::Keyboard::Space) yun.fire();

                break;

            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up) upFlag = false;
                if (event.key.code == sf::Keyboard::Down) downFlag = false;
                if (event.key.code == sf::Keyboard::Left) leftFlag = false;
                if (event.key.code == sf::Keyboard::Right) rightFlag = false;

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
    if (leftFlag && x > 0) x -= SPRITE_SPEED;
    if (rightFlag && x < game.getSize().x - yun._size) x += SPRITE_SPEED;
    if (upFlag && y > 0) y -= SPRITE_SPEED;
    if (downFlag && y < game.getSize().y - yun._size) y += SPRITE_SPEED;
    game.moveEntity(&yun, x, y);
}

void Game::refreshDisplay(){
    // Clear the window and apply grey background
    game.clear(sf::Color(127,127,127));

    game.drawEntity(&yun);

    // end the current frame
    game.display();
}
// Methodes de déplacement
void Game::moveEntity(Player *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);

}

void Game::moveEntity(Enemy *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);
}

void Game::moveEntity(Boss *object, float x, float y){
    object->_x += x;
    object->_y += y;
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
void Game::drawEntity(Player *object){
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

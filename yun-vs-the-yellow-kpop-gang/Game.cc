#include "Game.hh"
#define PI 3.141592653

Game::Game():
    sf::RenderWindow(sf::VideoMode(800, 600), "Yun VS The Yellow K-Pop Gang !!")
{
    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);
}

Game::Game(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name)
{
    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);
}

Game::~Game(){
    delete(this);
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

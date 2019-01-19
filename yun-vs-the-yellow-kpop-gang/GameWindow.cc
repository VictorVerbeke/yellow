#include "GameWindow.hh"
#define PI 3.141592653

GameWindow::GameWindow():
    sf::RenderWindow(sf::VideoMode(800, 600), "Yun VS The Yellow K-Pop Gang !!")
{
    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);
}

GameWindow::GameWindow(sf::VideoMode mode, string name) :
    sf::RenderWindow(mode, name)
{
    //setIcon("images/icon.png");
    setMouseCursorVisible(false);
    setVerticalSyncEnabled(false);
    setFramerateLimit(60);
    setActive(true);
}

GameWindow::~GameWindow(){
    delete(this);
}


// Methodes de déplacement
void GameWindow::moveEntity(Player *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);

}

void GameWindow::moveEntity(Enemy *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);
}

void GameWindow::moveEntity(Boss *object, float x, float y){
    object->_x += x;
    object->_y += y;
    object->_sprite.setPosition(object->_x, object->_y);
}

void GameWindow::moveEntity(Pellet *object){
    object->_x = object->_x + (object->_speed) * cos(object->_direction * PI / 180);
    object->_y = object->_y + (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);
}

void GameWindow::moveEntity(PowerUp *object){
    object->_x = object->_x + (object->_speed) * cos(object->_direction * PI / 180);
    object->_y = object->_y + (object->_speed) * sin(object->_direction * PI / 180);
    object->_sprite.setPosition(object->_x, object->_y);
}

// Methodes d'affichage
void GameWindow::drawEntity(Player *object){
    draw(object->_sprite);
}

void GameWindow::drawEntity(Boss *object){
    draw(object->_sprite);
}

void GameWindow::drawEntity(Enemy *object){
    draw(object->_sprite);
}

void GameWindow::drawEntity(PowerUp *object){
    draw(object->_sprite);
}

void GameWindow::drawEntity(Pellet *object){
    draw(object->_sprite);
}

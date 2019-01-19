#include "GameWindow.hh"

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

template <typename T>
void GameWindow::setPosition(T object, float x, float y){
    try {
        object._sprite.setPosition(x, y);
        object._x = x;
        object._y = y;
    } catch (exception const& ex){
        cout << "Exception: " << ex.what() << endl;
    }
}

template <typename T>
void GameWindow::drawItem(T object){
    try {
        this->draw(object._sprite);
    } catch (exception const& ex){
        cout << "Exception: " << ex.what() << endl;
    }
}

#include <iostream>
#include "Player.hh"
#include "Game.hh"
#include "Enemy.hh"
#include "Pellet.hh"
#include "Boss.hh"

#define SPRITE_SPEED 2

using namespace std;

int main ()
{
    Game game(sf::VideoMode(800, 600), "My window");
    Player yun(0, 0, 100, "images/yun_test_100.png");

    // Flags for key pressed
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    float x = 0;
    float y = 0;
    // run the program as long as the window is open
    while (game.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
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

        // Update coordinates
        x = 0;
        y = 0;
        if (leftFlag && x > 0) x -= SPRITE_SPEED;
        if (rightFlag && x < game.getSize().x - yun._size) x += SPRITE_SPEED;
        if (upFlag && y > 0) y -= SPRITE_SPEED;
        if (downFlag && y < game.getSize().y - yun._size) y += SPRITE_SPEED;

        // Clear the window and apply grey background
        game.clear(sf::Color(127,127,127));

        game.moveEntity(&yun, x, y);
        game.drawEntity(&yun);
        // end the current frame
        game.display();


    }

    return 0;
}

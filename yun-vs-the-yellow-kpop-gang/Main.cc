#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hh"
#include <iostream>

#define SPRITE_SPEED 1

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Player yun(10, 10, 700, "images/yun_test.png");

    // Flags for key pressed
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    float x = 10.0;
    float y = 10.0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    // "close requested" event: we close the window
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    // Process the up, down, left and right keys
                    if (event.key.code == sf::Keyboard::Up) upFlag = true;
                    if (event.key.code == sf::Keyboard::Down) downFlag = true;
                    if (event.key.code == sf::Keyboard::Left) leftFlag = true;
                    if (event.key.code == sf::Keyboard::Right) rightFlag = true;

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
        if (leftFlag) x -= SPRITE_SPEED;
        if (rightFlag) x += SPRITE_SPEED;
        if (upFlag) y -= SPRITE_SPEED;
        if (downFlag) y += SPRITE_SPEED;

        // Clear the window and apply grey background
        window.clear(sf::Color(127,127,127));

        yun._sprite.setPosition(x, y);

        window.draw(yun._sprite);

        // end the current frame
        window.display();

        cout << x << endl;
    }

    return 0;
}

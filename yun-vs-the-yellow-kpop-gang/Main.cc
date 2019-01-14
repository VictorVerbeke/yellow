#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hh"

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    Player yun(10, 10, 700, "images/yun_test.png");

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

                default:
                    break;
            }
        }

        window.draw(yun.getSprite());

        // end the current frame
        window.display();
    }

    return 0;
}

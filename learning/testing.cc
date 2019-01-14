#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main ()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnable(true);

    // change the position of the window (relatively to the desktop)
    window.setPosition(sf::Vector2i(10, 10));

    // change the size of the window
    window.setSize(sf::Vector2u(640, 480));

    // change the title of the window
    window.setTitle("SFML window");

    // get the size of the window
    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    cout << width << endl;
    cout << height << endl;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

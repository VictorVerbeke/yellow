#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(10, 10));
    window.setSize(sf::Vector2u(640, 480));
    window.setTitle("SFML window");

    // get the size of the window
    sf::Vector2u size = window.getSize();
    cout << size.x << endl;
    cout << size.y << endl;

    // Create shapes
    sf::CircleShape shape(50.f);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::Left :
                        shape.setFillColor(sf::Color(100,0,100));
                        break;
                    case sf::Keyboard::Right :
                        shape.setFillColor(sf::Color(0,100,100));
                        break;
                    case sf::Keyboard::Up :
                        shape.setFillColor(sf::Color(100,100,0));
                        break;
                    case sf::Keyboard::Down :
                        shape.setFillColor(sf::Color(255,255,255));
                        break;
                    default:
                        break;
                }
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.draw(shape);
    }

    return 0;
}

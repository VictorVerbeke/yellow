#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

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

                case sf::Event::Resized:
                    cout << "new width: " << event.size.width << endl;
                    cout << "new height: " << event.size.height << endl;
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::N)
                        cout << "YOU CANT SAY THE N-WORD WHITE BOY" << endl;

                    break;

                default:
                    break;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        sf::Text text;

        sf::Font font;
        if (!font.loadFromFile("fonts/Roboto-Light.ttf")) {
            cout << "Error loading font" << endl;
            return 1;
        }

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("Cyberpunk 2077");

        // set the character size
        text.setCharacterSize(40); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Yellow);

        window.draw(text);

        // end the current frame
        window.display();
    }

    return 0;
}

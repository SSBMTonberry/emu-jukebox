#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "fmt/format.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "emu-jukebox");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

        }
        // Clear screen
        window.clear(sf::Color(51,108,198));
        window.display();
    }
    return 0;
}
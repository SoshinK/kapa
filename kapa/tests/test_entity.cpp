#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "entities.h"

int main()
{
    std::vector<std::string> textnames = {"Entity_Default", "kitten_texture"};
    std::vector<std::string> textpaths = {"resources/textures/entity.png", "resources/textures/kapa_texture.png"};
    TextureManager tm (textnames, textpaths);

    Entity entityInstance(tm);

    sf::Clock globalClock;
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        entityInstance.control();
        entityInstance.logic(window, globalClock);
        entityInstance.physics(window, globalClock);
        window.clear(sf::Color(0, 0, 0, 255));
        entityInstance.draw(window);
        window.display();
    }
}
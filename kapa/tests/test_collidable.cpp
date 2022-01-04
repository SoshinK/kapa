#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "engine.h"
#include "engine.h"


int main()
{
    std::vector<std::string> textnames = {"Entity_Default", "kitten_texture"};
    std::vector<std::string> textpaths = {"resources/textures/entity.png", "resources/textures/kapa_texture.png"};
    TextureManager tm (textnames, textpaths);
    EntitySet es;
    es.addObject("entity4", new CollidableCircle(tm, sf::Vector2f(149., 170.), 0.0, sf::Vector2f(2.1, 2.1), 1));
    es.addObject("entity5", new CollidableCircle(tm, sf::Vector2f(745., 850.), 90.0, sf::Vector2f(-2.1, -2.1), 2));
    es.dump();
    sf::Clock globalClock;
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Test Collidable");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        es.detectCollisions();
        es.doCycle(window, globalClock);
        window.display();
    }
    es.dump();
    return 0;
}

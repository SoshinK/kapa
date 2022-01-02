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
    std::map<std::string, Entity*> instances_set = {{"entity1", new Entity(tm)}};
    EntitySet es(instances_set);
    es.addObject("entity2", new Entity(tm, sf::Vector2f(245., 250.), 0.0, sf::Vector2f(0., 0.), 1));
    es.dump();
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
        es.doCycle(window, globalClock);
        window.display();
    }
    return 0;
}

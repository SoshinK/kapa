#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "entities.h"

int main()
{
    std::vector<std::string> textnames = {"Entity_Default", "kitten_texture"};
    std::vector<std::string> textpaths = {"resources/textures/entity.png", "resources/textures/kapa_texture.png"};
    TextureManager tm (textnames, textpaths);

    std::vector<Entity *> instances;
    instances.push_back(new Entity(tm));
    instances.push_back(new Entity(tm, sf::Vector2f(245., 250.), 0.0, sf::Vector2f(0., 0.), 1));

    // std::vector<Entity *> instances = {
    //     new Entity(tm),
    //     new Entity(tm, sf::Vector2f(245., 250.), 0.0, sf::Vector2f(0., 0.), 1),
    // };

    Entity entityInstance(tm);
    // Entity * hop = new Entity;
    // hop->control();
    // delete hop;
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
        for(uint i = 0; i < instances.size(); i++)
        {
            instances[i]->control();
            instances[i]->logic(window, globalClock);
            instances[i]->physics(window, globalClock);
            instances[i]->draw(window);
        }
        // entityInstance.control();
        // entityInstance.logic(window, globalClock);
        // entityInstance.physics(window, globalClock);
        // window.clear(sf::Color(0, 0, 0, 255));
        // entityInstance.draw(window);
        window.display();
    }
    for(uint i = 0; i < instances.size(); i++)
    {
        std::cout << *instances[i];
        delete instances[i];
    }
}
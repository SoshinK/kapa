#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "graphics.h"

class Entity
{
    public:
        Entity();
        Entity(TextureManager & tm);
        Entity(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id);
        virtual ~Entity();

        virtual void control();
        virtual void physics(sf::RenderWindow & window, sf::Clock & clock);
        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void draw(sf::RenderWindow & window);
    
        sf::Vector2f pos;
        float angle;
        sf::Vector2f velocity;
        sf::Vector2f scale;

        const std::string name;
        const uint id;
        bool isAlive;

        std::ostream & dump(std::ostream & os) const;

    private:
        TextureManager textureManager_;
        sf::Sprite sprite_;
        sf::Vector2i frame_;
        uint spriteSide_;
};

std::ostream & operator<<(std::ostream & os, const Entity & entity);



#endif
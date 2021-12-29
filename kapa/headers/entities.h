#ifndef ENTITIES_H
#define ENTITIES_H

#include <SFML/Graphics.hpp>
#include "graphics.h"

class Entity
{
    public:
        Entity();
        Entity(TextureManager & tm);
        Entity(TextureManager & tm, sf::Vector2f pos, float angle);
        ~Entity();

        virtual void control();
        virtual void physics(sf::RenderWindow & window, sf::Clock & clock);
        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void draw(sf::RenderWindow & window);

        void loadTexture(const char* texturePath);
        void pushEvent();

        TextureManager textureManager;
        sf::Sprite sprite;
        sf::Vector2f scale;
        sf::Vector2f pos;
        float angle;
        sf::Vector2f velocity;
        sf::Vector2i frame;
        uint spriteSide;
};

#endif
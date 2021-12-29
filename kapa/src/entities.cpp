#include <string>
#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "entities.h"
#include "utils.h"

Entity::Entity():
    textureManager(TextureManager()),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(constants::defaultSpriteSide)
    {}

Entity::Entity(TextureManager & tm):
    textureManager(tm),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(100)
    {
        sprite.setTexture(textureManager.textures[std::string("Entity_Default")]);
    }

Entity::Entity(TextureManager & tm, sf::Vector2f newpos, float newangle):
    textureManager(tm),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(newpos),
    angle(newangle),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(100)
    {
        sprite.setTexture(textureManager.textures[std::string("Entity_Default")]);
    }


Entity::~Entity() {}


void Entity::draw(sf::RenderWindow & window)
{
    sprite.setOrigin(sf::Vector2f((float) spriteSide / 2, (float) spriteSide / 2));
    sprite.setTextureRect(sf::IntRect(frame.y * spriteSide, frame.x * spriteSide, spriteSide, spriteSide));
    sprite.setScale(scale);
    sprite.setPosition(pos);
    sprite.setRotation(angle);
    window.draw(sprite);
}

void Entity::control() {}
void Entity::physics(sf::RenderWindow & window, sf::Clock & clock) {}
void Entity::logic(sf::RenderWindow & window, sf::Clock & clock) {}



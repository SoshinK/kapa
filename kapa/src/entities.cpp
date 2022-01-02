#include <string>
#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "entities.h"
#include "utils.h"

Entity::Entity():
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    scale(sf::Vector2f(1.0f, 1.0f)),
    name("entity"),
    id(0),
    textureManager_(TextureManager()),
    sprite_(sf::Sprite()),
    frame_(sf::Vector2i(0, 0)),
    spriteSide_(constants::defaultSpriteSide)
    {}

Entity::Entity(TextureManager & tm):
    Entity()
    {
        textureManager_ = tm;
        sprite_.setTexture(textureManager_.textures[std::string("Entity_Default")]);
    }

Entity::Entity(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id):
    pos(pos),
    angle(angle),
    velocity(velocity),
    scale(sf::Vector2f(1.0f, 1.0f)),
    name("entity"),
    id(id),
    sprite_(sf::Sprite()),
    frame_(sf::Vector2i(0, 0)),
    spriteSide_(constants::defaultSpriteSide)
    {
        textureManager_ = tm;
        sprite_.setTexture(textureManager_.textures[std::string("Entity_Default")]);
    }


Entity::~Entity() {}


void Entity::draw(sf::RenderWindow & window)
{
    sprite_.setOrigin(sf::Vector2f((float) spriteSide_ / 2, (float) spriteSide_ / 2));
    sprite_.setTextureRect(sf::IntRect(frame_.y * spriteSide_, frame_.x * spriteSide_, spriteSide_, spriteSide_));
    sprite_.setScale(scale);
    sprite_.setPosition(pos);
    sprite_.setRotation(angle);
    window.draw(sprite_);
}

void Entity::control() {}
void Entity::physics(sf::RenderWindow & window, sf::Clock & clock) {}
void Entity::logic(sf::RenderWindow & window, sf::Clock & clock) {}

std::ostream & Entity::dump (std::ostream & os) const
{
    os << this->name \
        << "[id" << this->id << "] pos=" \
        << this->pos.x << ';' << this->pos.y\
        << " angle=" << this->angle \
        << " velocity=" << this->velocity.x << ';' << this->velocity.y \
        << std::endl;
    return os;
}

std::ostream & operator<< (std::ostream & os, const Entity & entity)
{
    return entity.dump(os);
}

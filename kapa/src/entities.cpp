#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "entities.h"
#include "utils.h"
#include "logic.h"

Entity::Entity():
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    scale(sf::Vector2f(1.0f, 1.0f)),
    // name("entity"),
    id(0),
    isAlive(true),
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
    // name("entity"),
    id(id),
    isAlive(true),
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
        << "[id" << this->id << "] isAlive=" << this->isAlive << " pos=" \
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

Pursuer::Pursuer():
    Entity(),
    // name("pursuer"),
    lastLaunchedRotation(0),
    lastLaunchedMoving(0),
    lastLaunchedVelocityUpdate(0)
{}

Pursuer::Pursuer(TextureManager & tm):
    Entity(tm),
    lastLaunchedRotation(0),
    lastLaunchedMoving(0),
    lastLaunchedVelocityUpdate(0)
{}

Pursuer::Pursuer(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id):
    Entity(tm, pos, angle, velocity, id),
    lastLaunchedRotation(0),
    lastLaunchedMoving(0),
    lastLaunchedVelocityUpdate(0)
{}

Pursuer::~Pursuer(){}

void Pursuer::updateVelocity(sf::RenderWindow & window, sf::Clock & clock)
{
    float descount_factor = 0.23;
    float velocity_coef = 25;
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedVelocityUpdate) > 0.1)
    {
        sf::Vector2i position2i = sf::Mouse::getPosition(window);
        sf::Vector2f position2f ((float)position2i.x, (float)position2i.y);
        sf::Vector2f direction = position2f - pos;
        if (vectorLen(direction) < 200)
        {
            velocity = sf::Vector2f(0., 0.);
        }
        else
        {
            normalizeVec(direction);
            velocity = velocity * descount_factor * descount_factor + direction;
            normalizeVec(velocity);
            velocity = velocity_coef * velocity;
        }     

            // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedVelocityUpdate = elapsed;
    }
}


void Pursuer::moveToMouse(sf::RenderWindow & window, sf::Clock & clock)
{
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedMoving) > 0.1)
    {
        sf::Vector2u size = window.getSize();
        this->updateVelocity(window, clock);
        sf::Vector2f old_pos = pos;
        pos += velocity;

        if (pos.x > (float)size.x || pos.x < 0. || pos.y > (float)size.y || pos.y < 0.)
        {
            pos = old_pos;
            velocity = sf::Vector2f(0., 0.);
        }
        lastLaunchedMoving = elapsed;
    }
}

void Pursuer::rotationToMouse(sf::RenderWindow & window, sf::Clock & clock)
{
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedRotation) > 0.1)
    {
        // float r = fRand(0, 180);
        // lastLaunchedRotation = clock();
        // angle = r;
        sf::Vector2i position2i = sf::Mouse::getPosition(window);
        sf::Vector2f position2f ((float)position2i.x, (float)position2i.y);
        sf::Vector2f direction = position2f - pos;
        if(std::abs(direction.y) < constants::eps)
            angle = 90;
        else
            angle = rad2deg(std::atan2(direction.y, direction.x));
            // std::cout << angle << '\n';

        // clock.restart();
        // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedRotation = elapsed;
    }
}

void Pursuer::logic(sf::RenderWindow & window, sf::Clock & clock)
{
    this->rotationToMouse(window, clock);
    this->moveToMouse(window, clock);
}

CollisionHandler::CollisionHandler():
    whereCollisionCumulative(sf::Vector2f(0., 0.)),
    isCollision(false),
    collisionRadius(0) 
    {}
CollisionHandler::CollisionHandler(const float radius):
    whereCollisionCumulative(sf::Vector2f(0., 0.)),
    isCollision(false),
    collisionRadius(radius) 
    {}
CollisionHandler::~CollisionHandler() {}


void CollisionHandler::processingRoutine(Entity* curEntity, sf::Vector2f whereCollision)
{
    isCollision = true;
    sf::Vector2f fromWhereCollision = whereCollision - curEntity->pos;
    normalizeVec(fromWhereCollision);
    whereCollisionCumulative += fromWhereCollision;
}

void CollisionHandler::finalRoutine(Entity* curEntity)
{
    if(isCollision)
    {
        normalizeVec(whereCollisionCumulative);
        CollidableCircle* curCollidable = (CollidableCircle*)curEntity;
        curCollidable->prevVelocity = sf::Vector2f(0., 0.);

        // float velocityLen = vectorLen(curCollidable->velocity);
        // normalizeVec(curCollidable->velocity);
        // std::cout << curEntity->id << " where: "<< whereCollisionCumulative.x <<' '<< whereCollisionCumulative.y << '\n';
        curCollidable->velocity = -2 * std::abs(dot(curCollidable->velocity, whereCollisionCumulative)) * whereCollisionCumulative + curCollidable->velocity;
        // std::cout << curEntity->id << " new velocity: "<< curCollidable->velocity.x <<' '<< curCollidable->velocity.y << '\n';
        sf::Vector2f prevPos = curCollidable->prevPos;
        curCollidable->prevPos = curCollidable->pos;
        curCollidable->pos = prevPos;
    }
}


CollidableCircle::CollidableCircle():
    Entity(),
    prevPos(pos),
    prevVelocity(velocity),
    collisionRadius(constants::defaultInteractionRadius)
    {}
CollidableCircle::CollidableCircle(TextureManager & tm):
    Entity(tm),
    prevPos(pos),
    prevVelocity(velocity),
    collisionRadius(constants::defaultInteractionRadius)
    {}
CollidableCircle::CollidableCircle(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id):
    Entity(tm, pos, angle, velocity, id),
    prevPos(pos),
    prevVelocity(velocity),
    collisionRadius(constants::defaultInteractionRadius)
    {}

void CollidableCircle::physics(sf::RenderWindow & window, sf::Clock & clock)
{
    this->processPhysEvents();
    this->updateVelocity(window, clock);
    this->friction();
    prevPos = pos;
    pos += velocity;
}

void CollidableCircle::processPhysEvents()
{
    CollisionHandler collisionHandler(collisionRadius);

    while(!eventPhysicsQueue.empty())
    {
        Event* curEvent = eventPhysicsQueue.front();
        switch (curEvent->type)
        {
        case EVENT_COLLISION:
            collisionHandler.processingRoutine(this, ((EventCollision*)curEvent)->whereCollision);
            delete (EventCollision*)curEvent;

            break;
        default:
            break;
        }
        eventPhysicsQueue.pop();

    }
    collisionHandler.finalRoutine(this);
    // std::cout << " HERE!\n";
}

void CollidableCircle::updateVelocity(sf::RenderWindow & window, sf::Clock & clock)
{
    // float discount_factor = 0.01;
    // float velocity_coef = 1.0;
    // sf::Vector2f oldVelocity = velocity;
    // // normalizeVec(velocity);
    // velocity = discount_factor * prevVelocity + velocity;
    // velocity = velocity * velocity_coef; 
    // prevVelocity = oldVelocity; 
}

void CollidableCircle::friction()
{
    float frictionFactor = 0.01;
    // std::cout << vectorLen(velocity) << '\n';
    if(vectorLen(velocity) < frictionFactor) velocity = sf::Vector2f(0., 0.);
    else velocity = velocity / vectorLen(velocity) * (vectorLen(velocity) - frictionFactor);
}

std::ostream & CollidableCircle::dump(std::ostream & os) const
{
    os << this->name \
    << "[id" << this->id << "] isAlive=" << this->isAlive << " pos=" \
    << this->pos.x << ';' << this->pos.y\
    << " prevPos=" << this->prevPos.x << ';' << this->prevPos.y \
    << " angle=" << this->angle \
    << " velocity=" << this->velocity.x << ';' << this->velocity.y \
    << " prevVelocity=" << this->prevVelocity.x << ';' << this->prevVelocity.y \
    << std::endl;
    return os;
}
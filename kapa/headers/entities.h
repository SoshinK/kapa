#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "graphics.h"
#include "logic.h"

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

        const char* name = "entity";
        const uint id;
        bool isAlive;

        virtual std::ostream & dump(std::ostream & os) const;

    private:
        TextureManager textureManager_;
        sf::Sprite sprite_;
        sf::Vector2i frame_;
        uint spriteSide_;
};

std::ostream & operator<<(std::ostream & os, const Entity & entity);

class Pursuer: public Entity
{
    public:
        Pursuer();
        Pursuer(TextureManager & tm);
        Pursuer(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id);
        ~Pursuer();

        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void updateVelocity(sf::RenderWindow & window, sf::Clock & clock);
        virtual void moveToMouse(sf::RenderWindow & window, sf::Clock & clock);
        virtual void rotationToMouse(sf::RenderWindow & window, sf::Clock & clock);
        const char* name = "pursuer";
        float lastLaunchedRotation;
        float lastLaunchedMoving;
        float lastLaunchedVelocityUpdate;
};

class CollisionHandler
{
    public:
        CollisionHandler();
        CollisionHandler(const float radius);
        ~CollisionHandler();

        void processingRoutine(Entity* curEntity, sf::Vector2f whereCollision);
        void finalRoutine(Entity* curEntity);
        sf::Vector2f whereCollisionCumulative;
        bool isCollision;
        const float collisionRadius;
};

class CollidableCircle: public Entity
{
    public:
        CollidableCircle();
        CollidableCircle(TextureManager & tm);
        CollidableCircle(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id);
        // virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void physics(sf::RenderWindow & window, sf::Clock & clock);
        virtual void updateVelocity(sf::RenderWindow & window, sf::Clock & clock);
        virtual void processPhysEvents();
        virtual void friction();
        virtual std::ostream & dump(std::ostream & os) const;
        // virtual void collisionHandler(sf::Vector2f whereCollision);
        const char* name = "collidablecircle";
        std::queue<Event*> eventPhysicsQueue;
        sf::Vector2f prevPos;
        sf::Vector2f prevVelocity;
        const float collisionRadius;
        sf::Vector2f whereCollisionCumulative;


};

// class ControllableCollidableCircle: public CollidableCircle
// {
//     public:
//         ControllableCollidableCircle();
//         ControllableCollidableCircle(TextureManager & tm);
//         ControllableCollidableCircle(TextureManager & tm, sf::Vector2f pos, float angle, sf::Vector2f velocity, uint id);
//         // virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
//         virtual void control();
// };


#endif
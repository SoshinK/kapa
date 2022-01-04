#include <SFML/Graphics.hpp>
#include "engine.h"
#include "utils.h"

EntitySet::EntitySet() {}
EntitySet::EntitySet(std::map<std::string, Entity*> entitySet):
    entitySet_(entitySet)
    {}
EntitySet::~EntitySet() 
{
    for(auto key=entitySet_.begin(); key != entitySet_.end(); key++)
        delete key->second;
    
    entitySet_.clear();
}

void EntitySet::addObject(std::string key, Entity* newEntity)
{
    if(entitySet_.find(key) == entitySet_.end())
        entitySet_[key] = newEntity;
}

void EntitySet::dump() const
{
    for(auto key=entitySet_.begin(); key != entitySet_.end(); key++)
        std::cout << "{" << key->first << "}" << *(key->second);
}

void EntitySet::doCycle(sf::RenderWindow & window, sf::Clock & clock) const
{
    for(auto key=entitySet_.begin(); key != entitySet_.end(); key++)
    {
        key->second->control();
        key->second->logic(window, clock);
        key->second->physics(window, clock);
    }
    window.clear();
    for(auto key=entitySet_.begin(); key != entitySet_.end(); key++)
        key->second->draw(window);
}

void EntitySet::detectCollisions()
{
    for(auto key=entitySet_.begin(); key != entitySet_.end(); key++)
        for(auto secondKey=entitySet_.begin(); secondKey != entitySet_.end(); secondKey++)
            if(key != secondKey)
                if(vectorLen(key->second->pos - secondKey->second->pos) < constants::defaultSpriteSide)
                {
                    EventCollision* collision = new EventCollision(secondKey->second->pos);
                    ((CollidableCircle*)key->second)->eventPhysicsQueue.push((Event*)collision);
                }
}

// void EntitySet::cleanObjects()
// {
//     for
// }
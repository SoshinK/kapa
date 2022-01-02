#include <SFML/Graphics.hpp>
#include "engine.h"

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
        key->second->draw(window);;
    }
}



// void EntitySet::cleanObjects()
// {
//     for
// }
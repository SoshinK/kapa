#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "entities.h"

class EntitySet
{
    public:
        EntitySet();
        EntitySet(std::map<std::string, Entity*> entitySet);
        ~EntitySet();
        void addObject(std::string key, Entity* newEntity);
        void doCycle(sf::RenderWindow & window, sf::Clock & clock) const;
        void cleanObjects();
        void dump() const;
        void detectCollisions();
    private:
        std::map<std::string, Entity*> entitySet_;
};




#endif
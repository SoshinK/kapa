#include <SFML/Graphics.hpp>
#include "logic.h"

Event::Event():
    type(Events::BASEEVENT)
    {}

Event::~Event() {}


EventMouseReached::EventMouseReached():
    Event()
    {
        type = Events::EVENT_MOUSE_REACHED;
    }
EventMouseReached::~EventMouseReached() {}

EventBoundaryReached::EventBoundaryReached():
    Event()
    {
        type = Events::EVENT_REACHED_BOUNDARIES;
    }
EventBoundaryReached::~EventBoundaryReached() {}

EventCollision::EventCollision():
    Event()
    {
        type = Events::EVENT_COLLISION;
    }
EventCollision::EventCollision(sf::Vector2f where):
    Event(),
    whereCollision(where)
    {
        type = Events::EVENT_COLLISION;
    }
    
EventCollision::~EventCollision() {}

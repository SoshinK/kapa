#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/Graphics.hpp>

enum Events
{   
    BASEEVENT,
    EVENT_MOUSE_REACHED,
    EVENT_REACHED_BOUNDARIES,
    EVENT_COLLISION,
};  

class Event
{
    public:
        Event();
        ~Event();
        int type;
};

class EventMouseReached: public Event
{
    public:
        EventMouseReached();
        ~EventMouseReached();
        // int type;

};

class EventBoundaryReached: public Event
{
    public:
        EventBoundaryReached();
        ~EventBoundaryReached();
        // int type;
        sf::Vector2f whereReached;
};

class EventCollision: public Event
{
    public:
        EventCollision();
        EventCollision(sf::Vector2f where);
        ~EventCollision();
        // int type;
        sf::Vector2f whereCollision;
};


#endif
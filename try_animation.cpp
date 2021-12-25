#include <vector>
#include <map>
#include <queue>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
// #include <ctime>

#define EPS 1e-5
#define PI 3.1415926

float rad2deg(float rad){return rad / PI * 180;}

enum Events
{   
    EVENT,
    EVENT_MOUSE_REACHED,
    EVENT_REACHED_BOUNDARIES,
};  

class Event
{
    public:
        Event();
        ~Event();
        int type;
};

float vectorLen(sf::Vector2f vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

void normalizeVec(sf::Vector2f & vec)
{
    float len = vectorLen(vec);
    if (len > 0)
    {
        vec.x /= len;
        vec.y /= len;
    }
}


Event::Event():
    type(Events::EVENT)
    {}

Event::~Event() {}


class EventMouseReached: public Event
{
    EventMouseReached();
    ~EventMouseReached() {}
    int type;

};

EventMouseReached::EventMouseReached():
    Event(),
    type(Events::EVENT_MOUSE_REACHED)
    {}

class EventBoundaryReached: public Event
{
    EventBoundaryReached();
    ~EventBoundaryReached() {}
    int type;
    sf::Vector2f whereReached;
};

EventBoundaryReached::EventBoundaryReached():
    Event(),
    type(Events::EVENT_REACHED_BOUNDARIES)
    {}

class TextureManager
{
    public:
        TextureManager();
        TextureManager(std::vector<std::string> textureNames, std::vector<std::string> texturePaths);
        ~TextureManager();

        std::map <std::string, sf::Texture> textures;
};

TextureManager::TextureManager() {}

TextureManager::TextureManager(std::vector<std::string> textureNames, std::vector<std::string> texturePaths)
{
    for(int i = 0; i < textureNames.size(); i++)
    {
        textures[textureNames[i]] = sf::Texture();
        textures[textureNames[i]].loadFromFile(texturePaths[i]);
    }
}

TextureManager::~TextureManager() {}

class Entity
{
    public:
        Entity();
        Entity(TextureManager* tm);
        Entity(TextureManager* tm, sf::Vector2f pos, float angle);
        // explicit Entity(const Entity & copy);
        ~Entity();
        virtual void control();
        virtual void physics(sf::RenderWindow & window, sf::Clock & clock);
        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void draw(sf::RenderWindow & window);

        void loadTexture(const char* texturePath);
        void pushEvent();

        TextureManager* textureManager;
        std::queue<Event> eventsQueue;
        sf::Sprite sprite;
        // sf::Texture texture;
        // unsigned higth;
        // unsigned width;
        sf::Vector2f scale;
        sf::Vector2f pos;
        float angle;
        sf::Vector2f velocity;
        sf::Vector2i frame;
        uint spriteSide;
};

Entity::Entity():
    // sprite(sf::Sprite()),
    // texture(sf::Texture()),
    textureManager(NULL),
    // higth(100),
    // width(100),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(100)
    {
        // this->loadTexture("entity.png");
        // this->loadTexture("kitten_texture.png");
        // texture = new sf::Texture;
        // sprite = new sf::Sprite;
        // if(!texture.loadFromFile("entity.png"))
        //     exit(-1);
        // sf::Sprite new_sprite(texture);
        // sprite = new_sprite;
    // sprite.setTexture(texture);

    }

Entity::Entity(TextureManager* tm):
    textureManager(tm),
    // higth(100),
    // width(100),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(sf::Vector2f(0.0, 0.0)),
    angle(0.),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(100)
    {
        // texture = tm.textures[std::string("Entity_Default")];
        sprite.setTexture(textureManager->textures[std::string("Entity_Default")]);
    }

Entity::Entity(TextureManager* tm, sf::Vector2f newpos, float newangle):
    textureManager(tm),
    // higth(100),
    // width(100),
    scale(sf::Vector2f(1.0f, 1.0f)),
    pos(newpos),
    angle(newangle),
    velocity(sf::Vector2f(.0, .0)),
    frame(sf::Vector2i(0, 0)),
    spriteSide(100)
    {
        // texture = tm.textures[std::string("Entity_Default")];
        sprite.setTexture(textureManager->textures[std::string("Entity_Default")]);
    }

// Entity::Entity(const Entity & that):
//     textureManager(that.textureManager),
//     eventsQueue(that.eventsQueue),
//     sprite(sf::Sprite()),
//     // texture(that.texture),
//     // higth(that.higth),
//     // width(that.width),
//     scale(that.scale),
//     pos(that.pos),
//     angle(that.angle),
//     velocity(that.velocity),
//     frame(that.frame),
//     spriteSide(that.spriteSide)
//     {
//         // std::copy(that.texture, that.texture + 1, texture);
//         sprite.setTexture(textureManager->textures[std::string("Entity_Default")]);
//     }

// Vector<T>::Vector(const Vector & that):
//   Capacity_(that.Capacity_),
//   Size_(that.Size_),
//   Data_(new T [Capacity_])
//   {
//   std::copy(that.Data_, that.Data_ + Capacity_, Data_);
//   VERIFY;
//   }

Entity::~Entity() 
{
    // delete texture;
    // delete sprite;    
    // delete texture;
}

// void Entity::loadTexture(const char* texturePath)
// {
//     if(!texture.loadFromFile(texturePath))
//         exit(-1);
//     sprite.setTexture(texture);
// }

void Entity::draw(sf::RenderWindow & window)
{
    sprite.setOrigin(sf::Vector2f((float) spriteSide / 2, (float) spriteSide / 2));
    sprite.setTextureRect(sf::IntRect(frame.y * spriteSide, frame.x * spriteSide, spriteSide, spriteSide));
    sprite.setScale(scale);
    sprite.setPosition(pos);
    sprite.setRotation(angle);
    // std::cout << angle << '\n';
    window.draw(sprite);
}

void Entity::control() {}
void Entity::physics(sf::RenderWindow & window, sf::Clock & clock) {}
void Entity::logic(sf::RenderWindow & window, sf::Clock & clock) {}

class MouseTracker: public Entity
{
    public:
        MouseTracker(): Entity() {}
        MouseTracker(TextureManager* tm): Entity(tm) {lastLaunchedRotation = 0;}
        MouseTracker(TextureManager* tm, sf::Vector2f pos, float angle): Entity(tm, pos, angle) {lastLaunchedRotation = 0;}
        ~MouseTracker(){}

        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void rotationToMouse(sf::RenderWindow & window, sf::Clock & clock);
        // float timeOfLife;
        float lastLaunchedRotation;
};

float fRand(float fMin, float fMax)
{
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void MouseTracker::rotationToMouse(sf::RenderWindow & window, sf::Clock & clock)
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
        if(std::abs(direction.y) < EPS)
            angle = 90;
        else
            angle = rad2deg(std::atan2(direction.y, direction.x));
            // std::cout << angle << '\n';

        // clock.restart();
        // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedRotation = elapsed;
    }
}

void MouseTracker::logic(sf::RenderWindow & window, sf::Clock & clock)
{
    this->rotationToMouse(window, clock);
}

class MovingEntity: public Entity
{
    public:
        MovingEntity(): Entity() {}
        MovingEntity(TextureManager* tm): Entity(tm) {
            // lastLaunchedCollision = 0; 
            lastLaunchedVelocityUpdate = 0; 
            lastLaunchedMoving = 0;
        }
        MovingEntity(TextureManager* tm, sf::Vector2f pos, float angle): Entity(tm, pos, angle) {
            // lastLaunchedCollision = 0; 
            lastLaunchedVelocityUpdate = 0; 
            lastLaunchedMoving = 0;
        }
        ~MovingEntity(){}

        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        // virtual void physics(sf::RenderWindow & window, sf::Clock clock);
        virtual void updateVelocity(sf::RenderWindow & window, sf::Clock & clock);
        virtual void moveToMouse(sf::RenderWindow & window, sf::Clock & clock);
        // float timeOfLife;
        // float lastLaunchedCollision;
        float lastLaunchedMoving;
        float lastLaunchedVelocityUpdate;
};


void MovingEntity::updateVelocity(sf::RenderWindow & window, sf::Clock & clock)
{
    float descount_factor = 0.1;
    float velocity_coef = 1;
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedVelocityUpdate) > 0.1)
    {
        // float r = fRand(0, 180);
        // lastLaunchedRotation = clock();
        // angle = r;
        sf::Vector2i position2i = sf::Mouse::getPosition(window);
        sf::Vector2f position2f ((float)position2i.x, (float)position2i.y);
        sf::Vector2f direction = position2f - pos;
        if (vectorLen(direction) < 10)
        {
            velocity = sf::Vector2f(0., 0.);
        }
        else
        {
            normalizeVec(direction);
            velocity = velocity * descount_factor + velocity_coef * direction;
        }     

            // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedVelocityUpdate = elapsed;
    }
}

// void 
// void MovingEntity::physics(sf::RenderWindow & window, sf::Clock clock)
// {   
//     float elapsed = clock.getElapsedTime().asSeconds();
//     if ((elapsed - lastLaunchedCollision) > 0.1)
//     {
        
        


//         lastLaunchedCollision = elapsed;
//     }

// }


void MovingEntity::moveToMouse(sf::RenderWindow & window, sf::Clock & clock)
{
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedMoving) > 0.1)
    {
        sf::Vector2u size = window.getSize();
        // sf::Vector2f old_velocity = velocity;
        this->updateVelocity(window, clock);
        sf::Vector2f old_pos = pos;
        pos += velocity;

        if (pos.x > (float)size.x || pos.x < 0. || pos.y > (float)size.y || pos.y < 0.)
        {
            pos = old_pos;
            velocity = sf::Vector2f(0., 0.);
        }

        // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedMoving = elapsed;
    }
}

void MovingEntity::logic(sf::RenderWindow & window, sf::Clock & clock)
{
    this->moveToMouse(window, clock);
}

class MovingRotatingEnitity: public Entity
{
    public:
        MovingRotatingEnitity(): Entity() {}
        MovingRotatingEnitity(TextureManager* tm): Entity(tm) {}
        MovingRotatingEnitity(TextureManager* tm, sf::Vector2f pos, float angle): Entity(tm, pos, angle) {}
        ~MovingRotatingEnitity(){}

        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        virtual void updateVelocity(sf::RenderWindow & window, sf::Clock & clock);
        virtual void moveToMouse(sf::RenderWindow & window, sf::Clock & clock);
        virtual void rotationToMouse(sf::RenderWindow & window, sf::Clock & clock);
        // float timeOfLife;
        float lastLaunchedRotation;
        // float timeOfLife;
        // float lastLaunchedCollision;
        float lastLaunchedMoving;
        float lastLaunchedVelocityUpdate;
};

void MovingRotatingEnitity::updateVelocity(sf::RenderWindow & window, sf::Clock & clock)
{
    float descount_factor = 0.23;
    float velocity_coef = 25;
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedVelocityUpdate) > 0.1)
    {
        // float r = fRand(0, 180);
        // lastLaunchedRotation = clock();
        // angle = r;
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


void MovingRotatingEnitity::moveToMouse(sf::RenderWindow & window, sf::Clock & clock)
{
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastLaunchedMoving) > 0.1)
    {
        sf::Vector2u size = window.getSize();
        // sf::Vector2f old_velocity = velocity;
        this->updateVelocity(window, clock);
        sf::Vector2f old_pos = pos;
        pos += velocity;

        if (pos.x > (float)size.x || pos.x < 0. || pos.y > (float)size.y || pos.y < 0.)
        {
            pos = old_pos;
            velocity = sf::Vector2f(0., 0.);
        }

        // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedMoving = elapsed;
    }
}

void MovingRotatingEnitity::rotationToMouse(sf::RenderWindow & window, sf::Clock & clock)
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
        if(std::abs(direction.y) < EPS)
            angle = 90;
        else
            angle = rad2deg(std::atan2(direction.y, direction.x));
            // std::cout << angle << '\n';

        // clock.restart();
        // std::cout << direction.x << ' '<<  direction.y << '\n';
        lastLaunchedRotation = elapsed;
    }
}

void MovingRotatingEnitity::logic(sf::RenderWindow & window, sf::Clock & clock)
{
    this->rotationToMouse(window, clock);
    this->moveToMouse(window, clock);
}

class ChasingCat : public MovingRotatingEnitity
{
    public:
        ChasingCat(): MovingRotatingEnitity() {spriteSide=32; frame = sf::Vector2i(0, 2); scale = sf::Vector2f(8., 8.); lastFrameUpdated = 0;}
        ChasingCat(TextureManager* tm): MovingRotatingEnitity(tm) {sprite.setTexture(textureManager->textures[std::string("kitten_texture")]); spriteSide=32; frame = sf::Vector2i(0, 2); scale = sf::Vector2f(8., 8.); lastFrameUpdated = 0;}
        ChasingCat(TextureManager* tm, sf::Vector2f pos, float angle): MovingRotatingEnitity(tm, pos, angle) {sprite.setTexture(textureManager->textures[std::string("kitten_texture")]); spriteSide=32; frame = sf::Vector2i(0, 2); scale = sf::Vector2f(8., 8.); lastFrameUpdated = 0;}
        ~ChasingCat(){}
        virtual void draw(sf::RenderWindow & window);
        virtual void updateFrame(sf::Clock & clock);

        virtual void logic(sf::RenderWindow & window, sf::Clock & clock);
        float lastFrameUpdated;
};

void ChasingCat::updateFrame(sf::Clock & clock)
{
    float elapsed = clock.getElapsedTime().asSeconds();
    if ((elapsed - lastFrameUpdated) > 0.2)
    {
        if (vectorLen(velocity) > 0)
        {
            if (frame.y == 1) frame.y = 0;
            else frame.y = (frame.y / 2 + 1) % 2 * 2;
        }
        else 
        {
            if (frame.y == 0 || frame.y == 2)
                frame.y = 1;
            else if (frame.y == 1)
                frame.y = 3;
            else if (frame.y == 3)
                frame.y = 5;
            else if (frame.y == 5)
                frame.y = 4;
            else 
                frame.y = 1;
        }
        // std::cout << elapsed << ' ' << lastFrameUpdated << ' ' << frame.y << '\n';
        lastFrameUpdated = elapsed;
    }
}

void ChasingCat::logic(sf::RenderWindow & window, sf::Clock & clock)
{
    this->updateFrame(clock);
    this->rotationToMouse(window, clock);
    this->moveToMouse(window, clock);
}

void ChasingCat::draw(sf::RenderWindow & window)
{
    float angle_old = angle;
    angle -= 90;
    MovingRotatingEnitity::draw(window);
    angle = angle_old;
}

int main()
{
    std::vector<std::string> textnames = {"Entity_Default", "kitten_texture"};
    std::vector<std::string> textpaths = {"entity.png", "kapa_texture.png"};
    TextureManager tm (textnames, textpaths);
    // sf::Texture texture;
    // if(!texture.loadFromFile("entity.png"))
    //     exit(-1);
    
    std::vector<Entity *> entities = {
        // new Entity(&tm, sf::Vector2f(150., 150.), 74),
        // new MouseTracker(&tm),
        // new MouseTracker(&tm, sf::Vector2f(250., 250.), 74),
        // new MouseTracker(&tm, sf::Vector2f(350., 350.), 174),
        // new MouseTracker(&tm, sf::Vector2f(750., 350.), 0.),
        // new MouseTracker(&tm, sf::Vector2f(550., 650.), 174),
        new ChasingCat(&tm, sf::Vector2f(950., 950.), 174),
        // new MovingEntity(&tm, sf::Vector2f(450., 550.), 0),
        // new MovingRotatingEnitity(&tm, sf::Vector2f(250., 150.), 0)
    };

    sf::Clock globalClock;
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(int i = 0; i < entities.size(); ++i)
        {
            entities[i]->physics(window, globalClock);
        }
        for(int i = 0; i < entities.size(); ++i)
        {
            entities[i]->logic(window, globalClock);
        }
        window.clear(sf::Color(255, 255, 255, 255));
        for(int i = 0; i < entities.size(); ++i)
            entities[i]->draw(window);
        // entity.draw(window);
        window.display();
    }
    // while(!entities.empty())
    // {
    //     delete entities[entities.size() - 1];
    //     entities.pop_back();
    // }
    // for(int i = 0; i < entities.size(); i++)
    // {
    //     delete entities[i];
    // }
    // delete entities[0];
    // up();
    // up();
//==============================
    // std::vector<std::string> textnames = {"entitydefault"};
    // std::vector<std::string> textpaths = {"entity.png"};
    // TextureManager tm (textnames, textpaths);

    // // sf::Texture a;
    // // a.loadFromFile("entity.png");
    // // std::vector<sf::Texture> vec;
    // // vec.push_back(a);
    // sf::Sprite sp;
    // sp.setTexture(tm.textures[std::string("Entity_Default")]);
    // // sf::Image image;
    // // FILE* data = fopen("entity.png", "rb");
    // // image.loadFromFile("entity.png");
    // // a.loadFromImage(image);
    // // a.create(200, 200);

    // sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //     window.clear();
    //     window.draw(sp);
    //     window.display();
    // }


   return 0;
// }
}

// #include <cstdlib>
// #include <iostream>

// using std::cout;
// using std::endl;

// class Cat
// {
// public:
//     void askForFood()
//     {
//         speak();
//         eat();
//     }
//     virtual void speak();// { cout << "Meow! "; }
//     virtual void eat();// { cout << "*champing*" << endl; }
// };
// void Cat::speak() { cout << "Meow! "; }
// void Cat::eat() { cout << "*champing*" << endl; }

// class CheshireCat : public Cat
// {
// public:
//     virtual void speak() ;//{ cout << "WTF?! Where\'s my milk? =) "; }
// };

// void CheshireCat::speak() { cout << "WTF?! Where\'s my milk? =) "; }


// int main()
// {
//     Cat * cats[] = { new Cat, new CheshireCat };

//     cout << "Ordinary Cat: "; cats[0]->askForFood();
//     cout << "Cheshire Cat: "; cats[1]->askForFood();

//     delete cats[0]; delete cats[1];

//     Cat a;
//     a.speak();

//     return EXIT_SUCCESS;
// }
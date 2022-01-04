#include <cmath>
#include <SFML/Graphics.hpp>
#include "utils.h"

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

float rad2deg(float rad){return rad / constants::pi * 180;}

float dot(sf::Vector2f vec1, sf::Vector2f vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

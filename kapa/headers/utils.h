#include <SFML/Graphics.hpp>
namespace constants
{
    const int defaultSpriteSide(100);
    const float defaultInteractionRadius(50);
    const float pi(3.141592);
    const float eps(1e-5);
}

float vectorLen(sf::Vector2f vec);
void normalizeVec(sf::Vector2f & vec);
float rad2deg(float rad);
float dot(sf::Vector2f vec1, sf::Vector2f vec2);


#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include "graphics.h"

TextureManager::TextureManager() {}

TextureManager::TextureManager(std::vector<std::string> textureNames, std::vector<std::string> texturePaths)
{
    for(int i = 0; i < (int)textureNames.size(); i++)
    {
        textures[textureNames[i]] = sf::Texture();
        textures[textureNames[i]].loadFromFile(texturePaths[i]);
    }
}

TextureManager::~TextureManager() {}
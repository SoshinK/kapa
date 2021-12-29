#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

class TextureManager
{
    public:
        TextureManager();
        TextureManager(std::vector<std::string> textureNames, std::vector<std::string> texturePaths);
        ~TextureManager();

        std::map <std::string, sf::Texture> textures;
};


#endif
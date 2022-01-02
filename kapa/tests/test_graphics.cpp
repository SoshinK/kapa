#include <vector>
#include <string>
#include <iostream>
#include "graphics.h"


int main()
{
    std::vector<std::string> textnames = {"Entity_Default", "kitten_texture"};
    std::vector<std::string> textpaths = {"resources/textures/entity.png", "resources/textures/kapa_texture.png"};
    TextureManager tm (textnames, textpaths);
    std::cout << tm.textures.size();
    return 0;

}
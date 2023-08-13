#pragma once
#include <SFML/Graphics.hpp>

#include "../v2.h"

class GameTile
{
public:
    v2 pos{};
    sf::Texture texture;
    sf::Sprite sprite;

    GameTile(std::string textureName, v2 _pos);
    bool SetupSprite(std::string textureName);
};

class PropTile
{
public:
    v2 pos;
    sf::Texture texture;
    sf::Sprite sprite;

    PropTile(std::string textureName, v2 _pos, bool flip);
    ~PropTile();
    bool SetupSprite(std::string textureName, bool flip);
};

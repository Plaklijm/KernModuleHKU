#pragma once
#include <SFML/Graphics.hpp>

#include "Data.h"
#include "v2.h"

class Entity
{
public:
    v2 position = {};
    v2 posOffset = {};
    v2 bounds = {SCREENSIZE};
    sf::Sprite sprite;
    int dmg = 5;

protected:
    sf::Texture texture;
};

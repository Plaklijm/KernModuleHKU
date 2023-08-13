#include "GameTile.h"

GameTile::GameTile(std::string textureName, v2 _pos)
{
    if (!SetupSprite(textureName))
        return;
    
    pos = v2(_pos);
    sprite.setPosition(pos);
}

bool GameTile::SetupSprite(std::string textureName)
{
    if (!texture.loadFromFile(textureName))
        return false;

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.5625f, 1.5625f);
    return true;
}


PropTile::PropTile(std::string textureName, v2 _pos, bool flip)
{
    if (!SetupSprite(textureName, flip))
        return;
    
    pos = v2(_pos);
    sprite.setPosition(pos);
}

PropTile::~PropTile()
{
    delete this;
}

bool PropTile::SetupSprite(std::string textureName, bool flip)
{
    if (!texture.loadFromFile(textureName))
        return false;

    texture.setSmooth(true);
    sprite.setTexture(texture);
    if (flip)
        sprite.setScale(-3.f, 3.f);
    else
        sprite.setScale(3.f, 3.f);
    return true;
}

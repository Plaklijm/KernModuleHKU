#pragma once
#include "GameTile.h"
#include <vector>

class GameWorld
{
private:
    void SetupInitialState();
    void SetupTiles();
    void SetupPropTiles();
    
public:
    std::vector<std::vector<GameTile*>> tiles;
    std::vector<PropTile*> propTilesLeft;
    std::vector<PropTile*> propTilesRight;
    v2 backgroundGrid{};
    v2 propGrid{};
    
    GameWorld();

    void UpdateProps();
};

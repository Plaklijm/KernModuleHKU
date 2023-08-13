#include "GameWorld.h"

#include "../Data.h"

GameWorld::GameWorld()
{
    backgroundGrid = {9,6};
    propGrid = {11, 2};
    SetupInitialState();
}

void GameWorld::SetupInitialState()
{
    SetupTiles();
    SetupPropTiles();
}

void GameWorld::SetupTiles()
{
    tiles.clear();
    for (int i = 0; i < backgroundGrid.x; i++)
    {
        std::vector<GameTile *> row;
        row.push_back(new GameTile("assets/Level/roadleft.png", v2{0,static_cast<float>(i * 100)}));
        row.push_back(new GameTile("assets/Level/road.png", v2{100,static_cast<float>(i * 100)}));
        row.push_back(new GameTile("assets/Level/road.png", v2{200,static_cast<float>(i * 100)}));
        row.push_back(new GameTile("assets/Level/road.png", v2{300,static_cast<float>(i * 100)}));
        row.push_back(new GameTile("assets/Level/road.png", v2{400,static_cast<float>(i * 100)}));
        row.push_back(new GameTile("assets/Level/roadright.png", v2{500,static_cast<float>(i * 100)}));
        tiles.push_back(row);
    }
}

void GameWorld::SetupPropTiles()
{
    propTilesLeft.clear();
    propTilesRight.clear();
    for (int i = 0; i < propGrid.x; i++)
    {
        propTilesLeft.push_back(new PropTile("assets/Level/light.png", v2{7.5f, static_cast<float>(i * 150 - 300)}, false));
        propTilesRight.push_back(new PropTile("assets/Level/light.png", v2{592.5f, static_cast<float>(i * 150 - 300)}, true));
    }
}
 
void GameWorld::UpdateProps()
{
    for (int i = 0; i < propTilesLeft.size() - 1; i++)
    {
        
        if (propTilesLeft[i]->pos.y > SCREENHEIGHT)
        {
            propTilesLeft.erase(propTilesLeft.begin() + i);
            propTilesLeft.push_back(new PropTile("assets/Level/light.png", v2{7.5f, static_cast<float>(-300)}, false));
        }
        propTilesLeft[i]->pos.y += 2;
        propTilesLeft[i]->sprite.setPosition(propTilesLeft[i]->pos);
    }

    for (int i = 0; i < propTilesRight.size() - 1; i++)
    {
        
        if (propTilesRight[i]->pos.y > SCREENHEIGHT)
        {
            propTilesRight.erase(propTilesRight.begin() + i);
            propTilesRight.push_back(new PropTile("assets/Level/light.png", v2{592.5f, static_cast<float>(-300)}, true));
        }
        propTilesRight[i]->pos.y += 2;
        propTilesRight[i]->sprite.setPosition(propTilesRight[i]->pos);
    }
}




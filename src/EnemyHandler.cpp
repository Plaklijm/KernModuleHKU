#include <iostream>
#include "EnemyHandler.h"

#include <filesystem>
#include <fstream>


std::mt19937 range( static_cast<unsigned>(time(nullptr)) );

EnemyHandler::EnemyHandler()
{
    currentWave = 95;
    for (int i = 0; i < 2; i++)
    {
        InitWave(currentWave, 1);
    }
}

void EnemyHandler::Update(sf::RenderTarget& target, float time, HandleGameScore& gs)
{
    currentWave = time;

    if (currentWave > 100)
    {
        currentWave = 1;
    }

    SpawnHandler(time);
    
    if (enemies.size() <= 1)
        return;
    for (int i = 0; i < enemies.size() - 1; i++)
    {
        enemies[i]->Update(SCREENWIDTH, enemies);
        
        if (enemies[i]->position.y > enemies[i]->bounds.y)
        {
            gs.RecieveCoins();
            gs.RecieveScore(rand()%18);
            enemies.erase(enemies.begin() + i);
        }
        target.draw(enemies[i]->Display());
    }
}

void EnemyHandler::InitWave(int currentWave, float maxVel)
{
    switch (GenerateEnemyType(currentWave))
    {
    case NormalCar:
        enemies.push_back(new Enemy(ChooseRandomCar("NormalCar/"), 0.2f, maxVel, false, 20, .3f));
        break;
    case SportsCar:
        enemies.push_back(new Enemy(ChooseRandomCar("SportsCar/"), 0.45f, maxVel, false, 15, .1f));
        break;
    case Van:
        enemies.push_back(new Enemy(ChooseRandomCar("Van/"), 0.17f, maxVel, false, 30, .65f));
        break;
    case Truck:
        enemies.push_back(new Enemy(ChooseRandomCar("Truck/"), 0.14f, maxVel, false, 50, .8f));
        break;
    case PoliceCar:
        enemies.push_back(new Enemy(ChooseRandomCar("PoliceCar/"), 0.35f, maxVel, true, 17.5f, .2f));
        break;
    case count: break;
    case none: break;
    default: break;
    }
}

double EnemyHandler::GetChance(int val, int mean, int stddev) const
{
    double dif = (val - mean) / static_cast<double>(stddev);
    return std::exp(-0.5*dif*dif) / (RAD2PI * stddev);
}

std::string EnemyHandler::ChooseRandomCar(std::string type) const
{
    std::string path = "assets/Entities/Enemies/" + type;
    const auto dirIter = std::filesystem::directory_iterator(path);
    int fileCount = 0;

    for (auto& entry : dirIter)
    {
        if (is_regular_file(entry))
        {
            ++fileCount;
        }
    }
    
    return path + std::to_string(rand()%fileCount + 1) + ".png";
}

void EnemyHandler::SpawnHandler(float time)
{
    respawnRate++;
    
    if (respawnRate == interval)
    {
        InitWave(currentWave, 1 + time / 50);    
        respawnRate = 0;
    }
}

EnemyType EnemyHandler::GenerateEnemyType(int currentwave)
{
    static const double minchance = 0.0001;

    double enemyProbability[count] = {};

    // calculate probabilities of each enemy spawning
    double sum = 0;
    for(auto& i : enemyData)
    {
        double chance = GetChance( currentwave, i.naturalWave, i.spread );
        if(chance < minchance)
            continue;

        enemyProbability[i.enemy] += chance;
        sum += chance;
    }
    
    if(!sum)
        return none;

    // generate random number 'r' which is between 0,sum
    double r = std::uniform_real_distribution<double>(0,sum)(range);

    // use 'r' to choose our enemy
    for(int i = 0; i < count; ++i)
    {
        if(!enemyProbability[i])
            continue;
        
        if(r < enemyProbability[i])
            return static_cast<EnemyType>(i);
        else 
            r -= enemyProbability[i];
    }

    return none;
}

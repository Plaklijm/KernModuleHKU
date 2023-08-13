#pragma once
#include <random>
#include "Enemy.h"


enum EnemyType
{
    NormalCar,
    SportsCar,
    Van,
    Truck,
    PoliceCar,
    //////////
    //////////
    count,
    none = -1
};

struct EnemyInfo
{
    EnemyType enemy;
    int naturalWave;
    int spread;
};

constexpr EnemyInfo enemyData[] = {
    {NormalCar, 10,  20},
    {SportsCar, 75,  9},
    {Van,       40, 12},
    {Truck,     55, 8},
    {PoliceCar, 60, 10}
};  


class EnemyHandler
{
private:
    int wave = 1;
    int interval = 100;
    int respawnRate = 0;
    int currentWave;

    double GetChance(int val, int mean, int stddev) const;
    std::string ChooseRandomCar(std::string type) const;
    
    void SpawnHandler(float time);

    
public:
    EnemyHandler();

    void Update(sf::RenderTarget& target, float time, HandleGameScore& gs);
    void InitWave(int currentWave, float maxVel);
    
    EnemyType GenerateEnemyType(int currentwave);
    std::vector<Enemy*> enemies;
};

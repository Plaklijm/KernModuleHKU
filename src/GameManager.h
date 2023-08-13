#pragma once
#include "EnemyHandler.h"
#include "Player.h"
#include "UI.h"
#include "Level/GameWorld.h"
#include "chrono"

struct GameData
{
    int score;
    int time;
    int coins;
    int highScore;
    v2 playerLocation;
    int stage;
};

using namespace std::chrono;

class GameManager
{
public:
    HandleGameScore gs;
    Player* p = new Player;
    UI* ui= new UI();
    GameWorld* gameWorld = new GameWorld();
    EnemyHandler* enemyHandler = new EnemyHandler();
    bool bstartGame = false;
    bool police = false;   
    int coins = {};
    int score = {};
    
private:
    v2 mousePos{};
    int collionCheck;
    float time;
    time_point<steady_clock> m_StartTime;
    
public:
    GameManager();
    void Update(sf::RenderWindow& target, bool bmousePressed);
    void RenderGame(sf::RenderTarget& target);
    bool CheckCollision();
    void StartGame();



private:
    void StartTimer();
    float GetTimerDuration();
};

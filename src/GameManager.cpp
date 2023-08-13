#include "GameManager.h"

#include <iostream>


GameManager::GameManager()
{
    StartTimer();
    ui->SetPlayer(p);
}

void GameManager::Update(sf::RenderWindow& target, bool bmousePressed)
{
    if (p->bDead)
    {
        ui->Died(target);
        return;
    }
    
    // get the current mouse position in the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(target);
    mousePos = { float(pixelPos.x), float(pixelPos.y) };
    
    gameWorld->UpdateProps();

    //RenderGame
    RenderGame(target);

    //EnemyUpdate
    enemyHandler->Update(target, GetTimerDuration(), gs);

    //PlayerUpdate
    p->Move();
    target.draw(p->Display());
    target.draw(p->ShieldDisplay());
    


    //UpdateUI
    ui->Update(mousePos, bmousePressed, GetTimerDuration(), gs);
    ui->Display(target);

    
    if (CheckCollision())
    {
        ui->DmgShield(police);
        score -= 500;
        if (score < 0)
        {
            score = 0;
        }
    }
}

void GameManager::RenderGame(sf::RenderTarget& target)
{
    for (int i = 0; i < gameWorld->backgroundGrid.x; i++)
    {
        for (int j = 0; j < gameWorld->backgroundGrid.y; j++)
        {
            target.draw(gameWorld->tiles[i][j]->sprite);
        } 
    }
    
    for (int i = 0; i < gameWorld->propTilesLeft.size() - 1; i++)
    {
        target.draw(gameWorld->propTilesLeft[i]->sprite);
    }
    for (int i = 0; i < gameWorld->propTilesRight.size() - 1; i++)
    {
        target.draw(gameWorld->propTilesRight[i]->sprite);
    } 
}

bool GameManager::CheckCollision()
{
    police = false;
    collionCheck++;
    if (collionCheck == 3)
    {
        for (int i = 0; i < enemyHandler->enemies.size() - 1; i++)
        {
            if (enemyHandler->enemies[i]->position.y > 800)
            {
                if (p->Collide(enemyHandler->enemies[i]))
                {
                    if (enemyHandler->enemies[i]->bisPolice)
                        police = true;
                    
                    collionCheck = 0;
                    enemyHandler->enemies.erase(enemyHandler->enemies.begin() + i);
                    return true;
                }
            }
        }
        collionCheck = 0;
    }
    return false;
}

void GameManager::StartGame()
{
    bstartGame = true;
}

void GameManager::StartTimer()
{
    m_StartTime = steady_clock::now();
}

float GameManager::GetTimerDuration()
{
    duration<float> duration = steady_clock::now() - m_StartTime;
    return duration.count();
}



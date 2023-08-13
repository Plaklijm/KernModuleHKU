#pragma once
#include "Enemy.h"
#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    ~Player();

    sf::CircleShape shield;
    sf::Sprite Display();
    sf::CircleShape ShieldDisplay();
    void Move();
    bool Collide(Enemy* p);
    bool Damage(bool police);

    void Upgrade(int i, int lvl);

    bool bDead = false;

private:
    int shieldPower = 0;
    int health = 100;
    float vel = 0.0f;
    float maxVel = 2.f;
    float accel = 0.5f;
    const float decel = 0.09f;
    float damp = .3f;

    float width;
    float height;
    
    void SpeedUpgrade(float lvl);
    void BounceUpgrade(float lvl);
    void ShrinkUpgrade(float lvl);
    void ShieldUpgrade(float lvl);
};

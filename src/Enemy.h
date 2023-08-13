#pragma once
#include "Entity.h"


class Enemy : public Entity
{
public:
    Enemy(std::string s, float iVel, float maxVel, bool bPolice, float mass, float friction);
    ~Enemy();
    
    bool bisPolice = false;

    float width;
    float height;

private:
    v2 velocity;
    float mass;
    float friction;
    v2 maxVel;
    float restitution = .5f;
    
    int offsetIndex{};

    int GetRandomPos();

public:
    void Update(float screenWidth, std::vector<Enemy*> enemies);
    
    void ApplyForce(const v2& force);
    void ApplyFriction();
    bool IsCollidingWith(const Enemy* other) const;
    void SolveCollisionWith(Enemy* other);
    
    sf::Sprite Display();
};

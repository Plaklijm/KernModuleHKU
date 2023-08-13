#include "Enemy.h"

#include <iostream>


Enemy::Enemy(std::string s, float iVel, float maxVel, bool bPolice, float mass, float friction)
{
    bisPolice = bPolice;
    this->maxVel = {maxVel + static_cast<float>(rand()%10) / 10, maxVel + .75f};

    velocity = {static_cast<float>(rand()%40 - 20) / 10, iVel * .2f};
    
    this->friction = friction;
    this->mass = mass;
    
    if (this->maxVel.x >= 10)
        this->maxVel.x = 10;
    if (this->maxVel.y >= 7.5f)
        this->maxVel.y = 7.5f;
    
    if (!texture.loadFromFile(s))
    {
        return; 
    }
    
    sprite.setTexture(texture);
    sprite.setScale(1.75f, 1.75f);
    
    sprite.setRotation(90);

    posOffset = {sprite.getLocalBounds().width * sprite.getScale().x / 2, sprite.getLocalBounds().height * sprite.getScale().y / 2};

    sprite.setOrigin(posOffset.x / sprite.getScale().x, posOffset.y / sprite.getScale().y);
    sprite.setPosition(v2(60 + GetRandomPos() - posOffset.x, -100));

    width = sprite.getGlobalBounds().width; 
    height = sprite.getGlobalBounds().height;
    
    position.x = sprite.getPosition().x;
    position.y = sprite.getPosition().y;
}

Enemy::~Enemy() = default;

sf::Sprite Enemy::Display()
{
    return sprite; 
}

int Enemy::GetRandomPos()
{
    offsetIndex = rand()%10 * 60;
    return offsetIndex;
}

void Enemy::Update(float screenWidth, std::vector<Enemy*> enemies)
{
    ApplyFriction();
    
    velocity.y += GRAVITY;
    velocity.y = std::min(std::max(velocity.y, -maxVel.y), maxVel.y);
    velocity.x = std::min(std::max(velocity.x, -maxVel.x), maxVel.x);
    position.x += velocity.x;
    position.y += velocity.y;

    // Check for collisions with left and right walls
    if (position.x - width / 2.0f < 0) {
        position.x = width / 2.0f;
        velocity.x = std::abs(velocity.x) * restitution;
    }
    if (position.x + width / 2.0f > screenWidth) {
        position.x = screenWidth - width / 2.0f;
        velocity.x = -std::abs(velocity.x) * restitution;
    }

    for (auto other : enemies) {
        if (other != this && IsCollidingWith(other)) {
            SolveCollisionWith(other);
        }
    }
    
    sprite.setPosition(position);
}

void Enemy::ApplyForce(const v2& force)
{
    v2 acceleration = {force.x / mass, force.y / mass};
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
}

void Enemy::ApplyFriction()
{
    if (velocity.x != 0.0f) {
        float frictionForce = -friction * mass * GRAVITY;
        float frictionDirection = (velocity.x > 0.0f) ? -1.0f : 1.0f;
        ApplyForce({frictionForce * frictionDirection, 0.0f});
    }
}


bool Enemy::IsCollidingWith(const Enemy* other) const {
    return std::abs(position.x - other->position.x) < (width + other->width) / 2.0f &&
           std::abs(position.y - other->position.y) < (height + other->height) / 2.0f;
}

void Enemy::SolveCollisionWith(Enemy* other) {
    // Swap velocities along x-axis
    velocity.x *= restitution;
    other->velocity.x *= restitution;
    std::swap(velocity.x, other->velocity.x);
}
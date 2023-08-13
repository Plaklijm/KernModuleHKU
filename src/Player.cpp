#include "Player.h"

#include <iostream>

#include "Enemy.h"

Player::Player()
{
    const std::string s = "assets/Entities/Player/hotdog.png";

    if (!texture.loadFromFile(s))
    {
        return;
    }
    
    sprite.setTexture(texture);
    sprite.setRotation(-90);
    sprite.setScale(1.5f, 1.5f);

    posOffset = {sprite.getLocalBounds().width * sprite.getScale().x / 2, sprite.getLocalBounds().height * sprite.getScale().y / 2};

    bounds = {posOffset.x, SCREENWIDTH - posOffset.x};

    sprite.setOrigin(posOffset.x / sprite.getScale().x, posOffset.y / sprite.getScale().y);
    sprite.setPosition(SCREENWIDTH / 2, SCREENHEIGHT - posOffset.y - 175);
    
    width = sprite.getGlobalBounds().width; 
    height = sprite.getGlobalBounds().height;

    shield.setRadius(35);
    shield.setOrigin(shield.getRadius(), shield.getRadius());
    shield.setFillColor(sf::Color(205, 231, 176, shieldPower));

}

Player::~Player() = default;

sf::Sprite Player::Display()
{
    return sprite;
}

sf::CircleShape Player::ShieldDisplay()
{
    return shield;
}

void Player::Move()
{
    position.x = sprite.getPosition().x;
    position.y = sprite.getPosition().y;

    bool left = false;
    bool right = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        left = true;
        if (-maxVel < vel) { vel = vel - accel; }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        right = true;
        if (vel < maxVel) { vel = vel + accel; }
    }

    if (!left && !right)
    {
        if (vel > 0.02f)
        {
            vel -= decel;
        }
        else if (vel < -0.02f)
        {
            vel += decel;
        }
        else
        {
            vel = 0;
        }
    }
    
    if (position.x < bounds.x)
    {
        sprite.setPosition(bounds.x, position.y);
        if (left)
            vel = 0;
        else
            vel = -(damp * vel);
    }

    if (position.x > bounds.y)
    {
        sprite.setPosition(bounds.y, position.y);
        if (right)
            vel = 0;
        else
            vel = -(damp * vel);
    }

    sprite.move(vel, 0);
    shield.setPosition(sprite.getPosition());
}

bool Player::Collide(Enemy* e)
{
    return  std::abs(position.x - e->position.x) < (width + e->width) / 2.0f &&
            std::abs(position.y - e->position.y) < (height + e->height) / 2.0f;
}

bool Player::Damage(bool police)
{
    if (police)
    {
        if (shieldPower > 0)
        {
            shieldPower = 0;
            shield.setFillColor(sf::Color(205, 231, 176, shieldPower));
        }
    }
    else
    {
        if (shieldPower > 0)
        {
            shieldPower -= 15;
            shield.setFillColor(sf::Color(205, 231, 176, shieldPower));
            return false;
        }
        if (health > 0)
        {
            health -= 25;
            std::cout << health << std::endl;
            return true;
        }
    }
    bDead = true;
    return true;
}

void Player::Upgrade(int i, int lvl)
{
    switch (i)
    {
    case 0:
        SpeedUpgrade(lvl);
        break;
    case 1:
        BounceUpgrade(lvl);
        break;
    case 2:
        ShrinkUpgrade(lvl);
        break;
    case 3:
        ShieldUpgrade(lvl);
        break;
    default:
        break;
    }
}

void Player::SpeedUpgrade(float lvl)
{
    maxVel += lvl * 0.02f;
    accel += lvl * 0.002f;
    std::cout << std::to_string(maxVel) << std::endl;
    std::cout << std::to_string(accel) << std::endl;
}

void Player::BounceUpgrade(float lvl)
{
    std::cout << std::to_string(lvl) << std::endl;
    damp += lvl * .025f;
}

void Player::ShrinkUpgrade(float lvl)
{
    shield.setScale(1.5f - lvl * 0.1f, 1.5f - lvl * 0.1f);
    sprite.setScale(1.5f - lvl * 0.05f, 1.5f - lvl * 0.05f);
    posOffset = {sprite.getLocalBounds().width * sprite.getScale().x / 2, sprite.getLocalBounds().height * sprite.getScale().y / 2};
    bounds = {posOffset.x, SCREENWIDTH - posOffset.x};
    sprite.setOrigin(posOffset.x / sprite.getScale().x, posOffset.y / sprite.getScale().y);
    std::cout << std::to_string(lvl) << std::endl;
}

void Player::ShieldUpgrade(float lvl)
{
    shieldPower = lvl * 15;
    shield.setFillColor(sf::Color(205, 231, 176, shieldPower));
}


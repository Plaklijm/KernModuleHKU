#include "UI.h"

#include <immintrin.h>
#include <iostream>

#include "GameManager.h"


UI::UI()
{
    if (!font.loadFromFile("assets/font/small_pixel.ttf"))
    {
        std::cout<< "No Font Found";
    }

    healthBar = {health, health1, health2, health3, health4};
    Shop = {UpgradeSpeed, UpgradeBounce, UpgradeShrink, UpgradeShield};
    Info = {Score, Time, Coins};

    InitSpriteObject(background);
    InitSpriteObject(youDied);

    for (auto &h : healthBar)
        InitSpriteObject(h);

    for (auto &s : Shop)
        InitSpriteObject(s);

    for (auto &i : Info)
        InitSpriteObject(i);
}

void UI::Update(v2 mousePos, bool bmousePressed, float time, HandleGameScore& gs)
{
    Info[1].cost = static_cast<int>(time);
    for (int i = 0; i < Shop.size(); i++)
    {
        if (Shop[i].sprite.getGlobalBounds().contains(mousePos) && bmousePressed && gs.GetCoins() > Shop[i].cost)
            Upgrade(i, gs);
    }

    Info[0].cost = gs.GetScore();
    Info[2].cost = gs.GetCoins();
}

void UI::InitSpriteObject(SpriteObject& obj)
{
    std::string s = obj.sPath;

    //Load texture and calculates position, if none is giving, set to bottemmiddle of screen
    if (!obj.loadTexture.loadFromFile(s))
    {
        std::cout<< "FILE NOT FOUND" << std::endl;  
        return;
    }
    
    obj.sprite.setTexture(obj.loadTexture);
    obj.sprite.setScale(obj.scale);
    obj.posOffset = {obj.sprite.getLocalBounds().width * obj.sprite.getScale().x / 2,
        obj.sprite.getLocalBounds().height * obj.sprite.getScale().y / 2};
    obj.sprite.setOrigin(obj.posOffset.x / obj.sprite.getScale().x, obj.posOffset.y / obj.sprite.getScale().y);
    
    if (obj.position.Magnitude() > 0)
        obj.sprite.setPosition(obj.position.x + obj.posOffset.x, obj.position.y - obj.posOffset.y);
    else
        obj.sprite.setPosition(SCREENWIDTH / 2,  SCREENHEIGHT - obj.posOffset.y);

    //Init text
    obj.text.setFont(font);
    obj.text.setFillColor(sf::Color::White);
    obj.text.setCharacterSize(13);
    obj.text.setPosition(obj.position.x + obj.sprite.getScale().x * 600, obj.position.y - obj.sprite.getScale().x * 475);
}

std::string UI::MaxLevel(int i) const
{
    std::string lvl = std::to_string(i);
    if (i >= 10)
        lvl = "Max";
    return lvl;
}

std::string UI::MaxCost(int c, int i) const
{
    std::string cost;
    if (i >= 10)
        cost = "Max";
    else
        cost = std::to_string(c);
    return cost;
}

void UI::Display(sf::RenderTarget& target)
{
    target.draw(background.sprite);

    for (auto &h : healthBar)
    {
        target.draw(h.sprite);    
    }
    
    //SHOP
    for (auto &s : Shop)
    {
        s.text.setString(s.sName + "\ncost: " + MaxCost(s.cost, s.lvl) + "\nLvl: " + MaxLevel(s.lvl));
        target.draw(s.sprite);
        target.draw(s.text);
    }

    for (auto &i : Info)
    {
        i.text.setString(i.sName + std::to_string(i.cost));
        target.draw(i.text);
        target.draw(i.sprite);
    }
}

void UI::Upgrade(int i, HandleGameScore& gs)
{
    if (Shop[i].lvl < Shop[i].maxLvl)
    {
        if (Shop[i].cost <= Info[2].cost)
        {
            gs.SetCoins(gs.GetCoins() - Shop[i].cost);
            Shop[i].lvl++;
            Shop[i].cost +=  static_cast<int>(Shop[i].lvl * 2.3f);
            _p->Upgrade(i, Shop[i].lvl);
        }
    }
}

void UI::DmgShield(bool police)
{
    if (Shop[3].lvl > 0)
    {
        Shop[3].lvl--;
    }
    if (_p->Damage(police))
    {
        if (police)
        {
            if (Shop[3].lvl > 0)
            {
                Shop[3].lvl = 0;
            }
            else if (!healthBar.empty())
            {
                healthBar.clear();
            }
        }
        else
            healthBar.pop_back();
    }
}

void UI::Died(sf::RenderTarget& target)
{
    target.draw(youDied.sprite);
}


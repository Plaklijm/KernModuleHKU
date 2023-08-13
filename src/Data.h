#pragma once
#include <iostream>

#include "v2.h"


constexpr int SCREENWIDTH = 600;
constexpr int SCREENHEIGHT = 1000;
const v2 SCREENSIZE = v2{SCREENWIDTH, SCREENHEIGHT};

constexpr  int FRAMERATE = 120;

constexpr float GRAVITY = 2.f;

const double PI = 3.14159265358979323846;
const double RAD2PI = std::sqrt(2*PI);


class HandleGameScore
{
public:
    int SCORE = 0;
    int COINS = 0;
    
    void RecieveScore(int amount)    { SCORE += amount; }
    void RecieveCoins()              { if (rand()%5 > 2) { COINS += rand()%8; } }
    void SetCoins(int amount)        { COINS = amount; }
    int GetCoins()                   { return COINS; }
    int GetScore()                   { return SCORE; }
};
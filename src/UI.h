#pragma once
#include "Player.h"

struct SpriteObject
{
    int maxLvl;
    std::string sPath;
    std::string sName;
    int cost;
    v2 scale{1,1};
    v2 position{};
    sf::Text text{};
    sf::Texture loadTexture{};
    sf::Sprite sprite{};
    v2 posOffset{};
    int lvl = 0;
};

class UI
{
private:
    Player* _p;
    sf::Font font;
    
    SpriteObject background{0, "assets/UI/Background.png", {}, 0, v2{1.f, 1.2f}};
    SpriteObject youDied{0, "assets/UI/YouDiedBig.png", {}, 0, v2{1.f, 1.f}};
    
    SpriteObject health{0, "assets/UI/health.png", {}, 0, v2{1,1}, v2{5,55}};
    SpriteObject health1{0, "assets/UI/health.png", {}, 0, v2{1,1}, v2{40,55}};
    SpriteObject health2{0, "assets/UI/health.png", {}, 0, v2{1,1}, v2{75,55}};
    SpriteObject health3{0, "assets/UI/health.png", {}, 0, v2{1,1}, v2{110,55}};
    SpriteObject health4{0, "assets/UI/health.png", {}, 0, v2{1,1}, v2{145,55}};
    
    std::vector<SpriteObject> healthBar;

    //Shop

    std::vector<SpriteObject> Shop;
    
    SpriteObject UpgradeSpeed{10, "assets/UI/speed.png", "Speed", 10, v2{0.1f, 0.1f},
        v2{5, 935}, };
    SpriteObject UpgradeBounce{10, "assets/UI/bounce.png", "Bounce", 10, v2{0.1f, 0.1f},
        v2{5, 995}};
    SpriteObject UpgradeShrink{10, "assets/UI/shrink.png", "Shrink", 10, v2{0.1f, 0.1f},
        v2{155, 935}};
    SpriteObject UpgradeShield{10, "assets/UI/shield.png", "Shield", 10, v2{0.1f, 0.1f},
        v2{155, 995}};
    
    //Info

    std::vector<SpriteObject> Info;
    
    SpriteObject Score{10, "assets/UI/score.png", "Score: ", {}, v2{0.0525f, 0.0525f},
        v2{425, 967.5f}};
    SpriteObject Time{10, "assets/UI/time.png", "Time: ", {}, v2{0.0525f, 0.0525f},
        v2{425, 940}};
    SpriteObject Coins{10, "assets/UI/coins.png", "Coins: ", {}, v2{0.0525f, 0.0525f},
      v2{425, 912.5f}};
    
    std::string MaxLevel(int i) const;
    std::string MaxCost(int c, int i) const;
    
public:
    UI();
    ~UI();
    
    void Update(v2 mousePos, bool bmousePressed, float time, HandleGameScore& gs);
    void InitSpriteObject(SpriteObject& obj);
    void Display(sf::RenderTarget& target);

    void Upgrade(int i, HandleGameScore& gs);
    void SetPlayer(Player* p) {_p = p;}
    void ShieldLvl();
    void DmgShield(bool police);

    void Died(sf::RenderTarget& target);
};

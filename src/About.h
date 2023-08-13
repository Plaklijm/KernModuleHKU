#pragma once
#include <SFML/Graphics.hpp>

class About
{
public:
    About();

    void Draw(sf::RenderTarget& target);
private:
    sf::Font font;
    sf::Text aboutText;
    sf::Text aboutTextBig;
    
};

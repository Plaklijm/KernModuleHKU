#include "About.h"

#include <iostream>

#include "Data.h"

About::About()
{
    if (!font.loadFromFile("assets/font/small_pixel.ttf"))
    {
        std::cout<< "No Font Found";
    }

    /// Very bad way to do it with all the \n and stuff.
    /// DONT DO IT THIS WAY!!
    /// Ugly code but it works and does the job
    /// pls forgive me <- (I forgive you)
    
    aboutTextBig.setFont(font);
    aboutText.setFont(font);
    aboutText.setFillColor(sf::Color::White);
    aboutTextBig.setFillColor(sf::Color::White);
    aboutText.setString("\n\n\n\n\n\n\n"
                        "A / D:                  Move Left/Right\n"
                        "W / S:                  Move Up/Down in menu\n"
                        "MouseClick:   Upgarde Player\n\n\n\n\n\n"
                        "Get the highest score you can!\n"
                        "Dont get hit by the cars!\n"
                        "Buy upgrades to improve your handling\n"
                        "Buy a shield to shied you from 1 car hit per lvl\n"
                        "But be careful! don't get hit by the police!\n"
                        "This will destroy your shield completely\n"
                        "Otherwise it will kill you and its GameOver\n"
                        "bounce only works if you let go before wall-hit\n");
    aboutTextBig.setString("Game made by: \n"
                            "Michiel van den Broek\n\n\n"
                            "Controls:\n\n\n\n\n\n"
                            "Game Rules:\n\n");
    aboutTextBig.setCharacterSize(24);
    aboutText.setCharacterSize(18);
    aboutText.setPosition(SCREENWIDTH / 10,200);
    aboutTextBig.setPosition(SCREENWIDTH / 13, 200);
}

void About::Draw(sf::RenderTarget& target)
{
    target.draw(aboutText);
    target.draw(aboutTextBig);
}

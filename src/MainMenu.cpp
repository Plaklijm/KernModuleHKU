#include "MainMenu.h"

MainMenu::MainMenu(v2 Size)
{
    if (!font.loadFromFile("assets/font/Vraoum.ttf"))
    {
        std::cout<< "No Font Found";
    }

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("PLAY_");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setOrigin(120, 0);
    mainMenu[0].setPosition(SCREENWIDTH / 2,200);

    //About
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("ABOUT_");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setOrigin(120, 0);
    mainMenu[1].setPosition(SCREENWIDTH / 2,350);
    
    //Quit
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::White);
    mainMenu[2].setString("QUIT_");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setOrigin(120, 0);
    mainMenu[2].setPosition(SCREENWIDTH / 2,500);
    
    mainMenu[MainMenuSelected].setFillColor(sf::Color(138, 129, 124));
}

MainMenu::~MainMenu()
{
}

void MainMenu::Draw(sf::RenderWindow& window)
{
    for (const auto& i : mainMenu)
    {
        window.draw(i);
    }
}

void MainMenu::MoveUp()
{
    if (MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        if (MainMenuSelected != -1)
        {
            MainMenuSelected--;
        }
        mainMenu[MainMenuSelected].setFillColor(sf::Color(138, 129, 124));
    }
}

void MainMenu::MoveDown()
{
    if (MainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
        if (MainMenuSelected != Max_main_menu - 1)
        {
            MainMenuSelected++;
        }
        mainMenu[MainMenuSelected].setFillColor(sf::Color(138, 129, 124));
    }
}

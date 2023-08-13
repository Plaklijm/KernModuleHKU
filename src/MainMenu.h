#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Data.h"

#define Max_main_menu 3
class MainMenu
{
public:
  MainMenu(v2 Size);
  ~MainMenu();
  void Draw(sf::RenderWindow& window);
  void MoveUp();
  void MoveDown();

  int MainMenuPressed(){
    return MainMenuSelected;
  }

private:
  int MainMenuSelected{};
  sf::Font font;
  sf::Text mainMenu[Max_main_menu];
};

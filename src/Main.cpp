#include "About.h"
#include "Player.h"
#include "MainMenu.h"
#include "Data.h"
#include "GameManager.h"


int main()
{
	GameManager* gm = {};
	sf::RenderWindow mainMenuWindow(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "EPIC RACE GAME OMG");
	MainMenu mainMenu(SCREENSIZE);
	mainMenuWindow.setFramerateLimit(FRAMERATE);

	while (mainMenuWindow.isOpen())
	{
		sf::Event event;
		while (mainMenuWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { mainMenuWindow.close(); }

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					sf::RenderWindow Play(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Game_Name");
					sf::RenderWindow About(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ABOUT");

					Play.setFramerateLimit(FRAMERATE);
					About.setFramerateLimit(FRAMERATE);

					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						gm = new GameManager();
						gm->StartGame();
						while (Play.isOpen())
						{
							bool bmousePressed = false;
							sf::Event playEvent;
							while (Play.pollEvent(playEvent))
							{
								if (playEvent.type == sf::Event::Closed)
								{
									Play.close();
								}
								if (playEvent.type == sf::Event::KeyPressed)
								{
									if (playEvent.key.code == sf::Keyboard::Escape)
									{
										Play.close();
									}
								}
								if (playEvent.type == sf::Event::MouseButtonReleased)
								{
									bmousePressed = true;
								}
							}

							About.close();
							Play.clear(sf::Color(35, 44, 51));
							if (gm->bstartGame)
							{
								gm->Update(Play, bmousePressed);
							}
							Play.display();
						}
					}
					if (x == 1)
					{
						::About a;
						while (About.isOpen())
						{
							sf::Event aboutEvent;
							while (About.pollEvent(aboutEvent))
							{
								if (aboutEvent.type == sf::Event::Closed)
								{
									About.close();
								}
								if (aboutEvent.type == sf::Event::KeyPressed)
								{
									if (aboutEvent.key.code == sf::Keyboard::Escape)
									{
										About.close();
									}
								}
							}
							Play.close();
							About.clear(sf::Color(35, 44, 51));
							a.Draw(About);
							About.display();
						}
					}
					if (x == 2)
					{
						mainMenuWindow.close();
						break;
					}
				}
			}
		}
		
		mainMenuWindow.clear(sf::Color(35, 44, 51));
		mainMenu.Draw(mainMenuWindow);
		mainMenuWindow.display();
	}
}

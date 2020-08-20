#include <time.h>
#include <string>
#include <iostream>

#include "Snake.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameModeMenu.h"
#include "Setup.h"

constexpr auto FRAME_LIMIT = 60;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Snake 1.2", sf::Style::Close);
	window.setFramerateLimit(FRAME_LIMIT);

	Setup gameSetup;
	gameSetup.setRenderWindow(&window);
	gameSetup.getResourceManager().loadFont("default", "fonts/arial.ttf");
	gameSetup.getResourceManager().loadTexture("snakeTxt", "skins/stolen.png");

	sf::Text fps;
	fps.setFont(*gameSetup.getResourceManager().getFont("default"));
	fps.setCharacterSize(24);
	fps.setFillColor(sf::Color::White);
	fps.setPosition(gameSetup.getRenderWindow()->getSize().x - 80.f, 0.f);

	sf::Clock clock;
	sf::Time deltaTime;

	MainMenu mainMenu(&gameSetup);
	gameSetup.getStateMachine().addState("mainMenu", &mainMenu);

	GameModeMenu gameModeMenu(&gameSetup);
	gameSetup.getStateMachine().addState("gameModeMenu", &gameModeMenu);

	PauseMenu pauseMenu(&gameSetup);
	gameSetup.getStateMachine().addState("pauseMenu", &pauseMenu);

	Snake snake(sf::Vector2u(20, 20), &gameSetup);
	gameSetup.getStateMachine().addState("snake", &snake);

	gameSetup.getStateMachine().setCurrentState("mainMenu");

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			gameSetup.getStateMachine().getCurrentState()->eventHandler(event);
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
			}			
		}

		deltaTime = clock.getElapsedTime();
		clock.restart();

		gameSetup.getStateMachine().getCurrentState()->update(deltaTime.asMilliseconds());
		fps.setString("Fps: " + std::to_string(int(1.f / deltaTime.asSeconds())));

		window.clear();
		gameSetup.getStateMachine().getCurrentState()->draw();
		window.draw(fps);
		window.display();
	}

	return 0;
}
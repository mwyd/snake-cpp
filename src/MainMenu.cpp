#include "MainMenu.h"

MainMenu::MainMenu(Setup* gameSetup) : m_gameSetup(gameSetup)
{
	sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();

	//play
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Play", m_gameSetup));
	options[0].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, renderWindowSize.y / 4));

	options[0].onclick = [this](Button& self) 
	{
		m_gameSetup->getStateMachine().setCurrentState("gameModeMenu"); 
	};

	options[0].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Green); };
	options[0].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };

	//exit
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Exit", m_gameSetup));
	options[1].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, renderWindowSize.y / 2));

	options[1].onclick = [this](Button& self) 
	{
		m_gameSetup->getRenderWindow()->close(); 
	};

	options[1].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Red); };
	options[1].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };
}

MainMenu::~MainMenu()
{

}

void MainMenu::eventHandler(sf::Event& event)
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].listen(event);
	}
}

void MainMenu::draw()
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].draw();
	}
}
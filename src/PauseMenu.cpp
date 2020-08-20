#include "PauseMenu.h"

PauseMenu::PauseMenu(Setup* gameSetup) : m_gameSetup(gameSetup)
{
	sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();

	//resume
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Resume", m_gameSetup));
	options[0].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, renderWindowSize.y / 4));

	options[0].onclick = [this](Button& self) 
	{
		m_gameSetup->getStateMachine().setCurrentState("snake"); 
	};

	options[0].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Green); };
	options[0].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };

	//main_menu
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Main menu", m_gameSetup));
	options[1].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, renderWindowSize.y / 2));

	options[1].onclick = [this](Button& self) 
	{
		m_gameSetup->getStateMachine().setCurrentState("mainMenu"); 
	};

	options[1].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Red); };
	options[1].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };
}

PauseMenu::~PauseMenu()
{

}

void PauseMenu::eventHandler(sf::Event& event)
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].listen(event);
	}
}

void PauseMenu::draw()
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].draw();
	}
}
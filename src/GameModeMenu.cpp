#include "GameModeMenu.h"

GameModeMenu::GameModeMenu(Setup* gameSetup) : m_gameSetup(gameSetup)
{
	sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();

	//classic
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Classic", m_gameSetup));
	options[0].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, 100.f));

	options[0].onclick = [this](Button& self)
	{
		dynamic_cast<Snake*>(m_gameSetup->getStateMachine().getState("snake"))->setClassicUpdater();
		m_gameSetup->getStateMachine().setCurrentState("snake");
	};

	options[0].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Green); };
	options[0].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };

	//arcade
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Arcade", m_gameSetup));
	options[1].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, 250.f));

	options[1].onclick = [this](Button& self)
	{
		dynamic_cast<Snake*>(m_gameSetup->getStateMachine().getState("snake"))->setArcadeUpdater();
		m_gameSetup->getStateMachine().setCurrentState("snake");
	};

	options[1].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Cyan); };
	options[1].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };

	//main_menu
	options.push_back(Button(sf::Vector2f(200.f, 100.f), "Main menu", m_gameSetup));
	options[2].setPosition(sf::Vector2f(renderWindowSize.x / 2 - 100.f, 400.f));

	options[2].onclick = [this](Button& self)
	{
		m_gameSetup->getStateMachine().setCurrentState("mainMenu");
	};

	options[2].onmouseenter = [](Button& self) { self.setFillColor(sf::Color::Red); };
	options[2].onmouseleave = [](Button& self) { self.setFillColor(self.getDefaultColor()); };
}

GameModeMenu::~GameModeMenu()
{

}

void GameModeMenu::eventHandler(sf::Event& event)
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].listen(event);
	}
}

void GameModeMenu::draw()
{
	for (int i = 0; i < options.size(); i++)
	{
		options[i].draw();
	}
}
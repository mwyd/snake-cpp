#pragma once
#include <vector>

#include "State.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Setup.h"
#include "Snake.h"

class GameModeMenu : public State
{
public:
	GameModeMenu(Setup* gameSetup);
	~GameModeMenu();

	void eventHandler(sf::Event& event)	override;
	void draw()	override;

private:
	Setup* m_gameSetup;
	std::vector<Button> options;
};




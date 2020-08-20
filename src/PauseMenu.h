#pragma once
#include <vector>

#include "State.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Setup.h"

class PauseMenu : public State
{
public:
	PauseMenu(Setup* gameSetup);
	~PauseMenu();

	void eventHandler(sf::Event& event) override;
	void draw()	override;

private:
	Setup* m_gameSetup;
	std::vector<Button> options;
};




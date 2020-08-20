#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "ResourceManager.h"

class Setup
{
public:
	Setup();
	~Setup();

	StateMachine& getStateMachine();
	ResourceManager& getResourceManager();

	void setRenderWindow(sf::RenderWindow* renderWindow);
	sf::RenderWindow* getRenderWindow();

private:
	StateMachine stateMachine;
	ResourceManager resourceManager;
	sf::RenderWindow* renderWindow;
};


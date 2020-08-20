#pragma once
#include <SFML/Graphics.hpp>

class State
{
public:
	State();
	~State();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void eventHandler(sf::Event& event);
};


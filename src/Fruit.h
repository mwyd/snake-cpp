#pragma once
#include <SFML/Graphics.hpp>

#include "Setup.h"

class Fruit : public sf::Sprite
{
public:
	Fruit(sf::Vector2u fruitSize, Setup* gameSetup);
	~Fruit();

	void spawn();

private:
	Setup* m_gameSetup;
	sf::Vector2u m_fruitSize;
};


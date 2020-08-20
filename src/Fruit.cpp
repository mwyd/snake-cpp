#include "Fruit.h"

Fruit::Fruit(sf::Vector2u fruitSize, Setup* gameSetup) : m_gameSetup(gameSetup), m_fruitSize(fruitSize)
{
	setTexture(*m_gameSetup->getResourceManager().getTexture("snakeTxt"));
	setTextureRect(sf:: IntRect(4 * fruitSize.x, 0, fruitSize.x, fruitSize.y));
}

Fruit::~Fruit()
{

}

void Fruit::spawn()
{
	sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();

	renderWindowSize.x = (renderWindowSize.x / m_fruitSize.x) - 2;
	renderWindowSize.y = (renderWindowSize.y / m_fruitSize.y) - 2;

	int x = ((rand() % renderWindowSize.x) * m_fruitSize.x) + m_fruitSize.x;
	int y = ((rand() % renderWindowSize.y) * m_fruitSize.y) + m_fruitSize.y;
	setPosition(sf::Vector2f(x , y));
}
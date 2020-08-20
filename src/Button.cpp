#include "Button.h"

Button::Button(sf::Vector2f size, sf::String label, Setup* gameSetup) : RectangleShape(size), m_gameSetup(gameSetup)
{
	text.setString(label);
	text.setFont(*gameSetup->getResourceManager().getFont("default"));
	setFillColor(defaultColor);
}

Button::~Button()
{

}

void Button::draw()
{
	m_gameSetup->getRenderWindow()->draw(*this);
	m_gameSetup->getRenderWindow()->draw(text);
}

void Button::setPosition(sf::Vector2f pos)
{
	RectangleShape::setPosition(pos);
	text.setPosition(getPosition());
}

void Button::listen(sf::Event& event)
{
	sf::Vector2f mousePos = m_gameSetup->getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_gameSetup->getRenderWindow()));

	if (getGlobalBounds().contains(mousePos))
	{
		onmouseenter(*this);
		mouseEntered = true;

		switch (event.type)
		{
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) onclick(*this);
				break;
		}	
	}
	else if (mouseEntered)
	{
		onmouseleave(*this);
		mouseEntered = false;
	}
}

sf::Color Button::getDefaultColor()
{
	return defaultColor;
}
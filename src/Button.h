#pragma once
#include <SFML/Graphics.hpp>
#include <String>
#include <functional>

#include "Setup.h"

class Button : public sf::RectangleShape
{
public:
	sf::Text text;
	std::function<void(Button&)> onclick = [](Button& self) {};
	std::function<void(Button&)> onmouseenter = [](Button& self) {};
	std::function<void(Button&)> onmouseleave = [](Button& self) {};

public:
	Button(sf::Vector2f size, sf::String label, Setup* gameSetup);
	~Button();

	void draw();
	void listen(sf::Event& event);
	void setPosition(sf::Vector2f pos);
	sf::Color getDefaultColor();

private:
	Setup* m_gameSetup;
	bool mouseEntered = false;
	sf::Color defaultColor = sf::Color(192, 192, 192);
};
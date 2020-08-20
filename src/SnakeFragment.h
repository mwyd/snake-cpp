#pragma once
#include <SFML/Graphics.hpp>

class SnakeFragment : public sf::Sprite
{
public:
	static const int SPRITE_HEAD = 0;
	static const int SPRITE_BODY = 1;
	static const int SPRITE_TURN = 2;
	static const int SPRITE_TAIL = 3;

	static const int DIRECTION_UP = 10;
	static const int DIRECTION_DOWN	= 11;
	static const int DIRECTION_LEFT	= 12;
	static const int DIRECTION_RIGHT = 13;

	int lastDirection = -1;
	int currentDirection = -1;
	int type = -1;

public:
	SnakeFragment(sf::Vector2u fragmentSize, std::shared_ptr<sf::Texture> snakeTxt);
	~SnakeFragment();

	void setSprite(int type);
	void adjustSprite(int nextDirection);

private:
	sf::Vector2u m_fragmentSize;
};


#include "SnakeFragment.h"

SnakeFragment::SnakeFragment(sf::Vector2u fragmentSize, std::shared_ptr<sf::Texture> snakeTxt) : m_fragmentSize(fragmentSize)
{
	setTexture(*snakeTxt);
	setOrigin(fragmentSize.x * 0.5, fragmentSize.y * 0.5);
}

SnakeFragment::~SnakeFragment()
{

}

void SnakeFragment::setSprite(int type)
{
	switch (type)
	{
		case SPRITE_HEAD:
			setTextureRect(sf::IntRect(3 * m_fragmentSize.x, 0, int(m_fragmentSize.x), int(m_fragmentSize.y)));
			this->type = SPRITE_HEAD;
			break;

		case SPRITE_BODY:
			setTextureRect(sf::IntRect(m_fragmentSize.x, 0, int(m_fragmentSize.x), int(m_fragmentSize.y)));
			this->type = SPRITE_BODY;
			break;

		case SPRITE_TURN:
			setTextureRect(sf::IntRect(2 * m_fragmentSize.x, 0, int(m_fragmentSize.x), int(m_fragmentSize.y)));
			this->type = SPRITE_TURN;
			break;

		case SPRITE_TAIL:
			setTextureRect(sf::IntRect(0, 0, int(m_fragmentSize.x), int(m_fragmentSize.y)));
			this->type = SPRITE_TAIL;
			break;
	}
}

void SnakeFragment::adjustSprite(int nextDirection)
{
	switch (currentDirection)
	{
	case DIRECTION_UP:
		if (type == SPRITE_TURN && nextDirection == DIRECTION_RIGHT) setRotation(180.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_RIGHT) setRotation(0.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_LEFT) setRotation(180.f);
		else setRotation(-90.f);
		break;

	case DIRECTION_DOWN:
		if (type == SPRITE_TURN && nextDirection == DIRECTION_LEFT) setRotation(0.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_RIGHT) setRotation(0.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_LEFT) setRotation(180.f);
		else setRotation(90.f);
		break;

	case DIRECTION_RIGHT:
		if (type == SPRITE_TURN && nextDirection == DIRECTION_DOWN) setRotation(-90.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_UP) setRotation(-90.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_DOWN) setRotation(90.f);
		else setRotation(0.f);
		break;

	case DIRECTION_LEFT:
		if (type == SPRITE_TURN && nextDirection == DIRECTION_UP) setRotation(90.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_UP) setRotation(-90.f);
		else if (type == SPRITE_TAIL && nextDirection == DIRECTION_DOWN) setRotation(90.f);
		else setRotation(180.f);
		break;
	}
}

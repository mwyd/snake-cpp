#include "Snake.h"

Snake::Snake(sf::Vector2u fragmentSize, Setup* gameSetup) : m_gameSetup(gameSetup), m_fragmentSize(fragmentSize)
{
	step = fragmentSize.x;
	fruits.push_back(Fruit(m_fragmentSize, m_gameSetup));

	spawn();
	fruits[0].spawn();

	score.setFont(*m_gameSetup->getResourceManager().getFont("default"));
	score.setCharacterSize(24);
	score.setFillColor(sf::Color::White);
}

Snake::~Snake()
{

}

void Snake::spawn()
{
	//head
	body.push_back(SnakeFragment(m_fragmentSize, m_gameSetup->getResourceManager().getTexture("snakeTxt")));
	body[0].lastDirection = SnakeFragment::DIRECTION_RIGHT;
	body[0].currentDirection = SnakeFragment::DIRECTION_RIGHT;
	body[0].setSprite(SnakeFragment::SPRITE_HEAD);
	body[0].setPosition(m_fragmentSize.x * 0.5, m_fragmentSize.y * 0.5);

	appendSnakeFragment();
	appendSnakeFragment();
}

void Snake::spawnFruit()
{
	Fruit newFruit = Fruit(m_fragmentSize, m_gameSetup);
	newFruit.spawn();
	fruits.push_back(newFruit);
}

void Snake::draw()
{
	for (auto fruit : fruits)
	{
		m_gameSetup->getRenderWindow()->draw(fruit);
	}

	for (int i = body.size() - 1; i >= 0 ; i--)
	{
		m_gameSetup->getRenderWindow()->draw(body[i]);
	}

	m_gameSetup->getRenderWindow()->draw(score);
}

void Snake::run()
{
	int j = body.size() - 2;

	for (int i = 1; i < body.size(); i++)
	{
		body[i].lastDirection = body[i].currentDirection;
		body[i].currentDirection = body[i - 1].lastDirection;
		body[j + 1].setPosition(body[j].getPosition());

		if (i != body.size() - 1)
		{
			if (body[i - 1].lastDirection != body[i - 1].currentDirection) body[i].setSprite(SnakeFragment::SPRITE_TURN);
			else body[i].setSprite(SnakeFragment::SPRITE_BODY);
		}

		body[i].adjustSprite(body[i - 1].currentDirection);
		j--;
	}

	body[0].lastDirection = body[0].currentDirection;
	body[0].adjustSprite(body[0].currentDirection);

	switch (body[0].currentDirection)
	{
		case SnakeFragment::DIRECTION_UP:
			body[0].move(sf::Vector2f(0.f, -step));
			break;

		case SnakeFragment::DIRECTION_DOWN:
			body[0].move(sf::Vector2f(0.f, step));
			break;

		case SnakeFragment::DIRECTION_RIGHT:
			body[0].move(sf::Vector2f(step, 0.f));
			break;

		case SnakeFragment::DIRECTION_LEFT:
			body[0].move(sf::Vector2f(-step, 0.f));
			break;
	}
}

void Snake::setArcadeUpdater()
{
	reset();

	updater = [this](float deltaTime)
	{
		fruitSpawnTimeA += deltaTime;

		if (fruitSpawnTimeA >= fruitSpawnTime)
		{
			spawnFruit();
			fruitSpawnTimeA -= fruitSpawnTime;
		}

		eaten();
		onKeyDown();
		run();

		score.setString("Score: " + std::to_string(getLength() - 3));

		sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();
		float halfSize = step / 2;

		if (body[0].getPosition().x < 0.f) body[0].setPosition(sf::Vector2f(renderWindowSize.x - halfSize, body[0].getPosition().y));
		else if (body[0].getPosition().x > renderWindowSize.x) body[0].setPosition(sf::Vector2f(halfSize, body[0].getPosition().y));
		else if (body[0].getPosition().y < 0.f) body[0].setPosition(sf::Vector2f(body[0].getPosition().x, renderWindowSize.y - halfSize));
		else if (body[0].getPosition().y > renderWindowSize.y) body[0].setPosition(sf::Vector2f(body[0].getPosition().x, halfSize));
	};
}

void Snake::setClassicUpdater()
{
	reset();

	updater = [this](float deltaTime)
	{
		if (eaten()) spawnFruit();
		
		onKeyDown();
		run();

		score.setString("Score: " + std::to_string(getLength() - 3));

		if (died()) reset();
	};
}

void Snake::update(float deltaTime)
{
	updateTimeA += deltaTime;

	if (updateTimeA >= updateTime)
	{
		updater(deltaTime);
		updateTimeA -= updateTime;
	}
}

void Snake::eventHandler(sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					m_gameSetup->getStateMachine().setCurrentState("pauseMenu");
					break;

				case sf::Keyboard::Num1:
					if (updateTime > minUpdateTime) updateTime -= 5;
					break;

				case sf::Keyboard::Num2:
					if (updateTime < maxUpdateTime) updateTime += 5;
					break;
			}
			break;

		case sf::Event::LostFocus:
			m_gameSetup->getStateMachine().setCurrentState("pauseMenu");
	}
}

void Snake::onKeyDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (body[0].currentDirection != SnakeFragment::DIRECTION_DOWN) body[0].currentDirection = SnakeFragment::DIRECTION_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (body[0].currentDirection != SnakeFragment::DIRECTION_UP) body[0].currentDirection = SnakeFragment::DIRECTION_DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (body[0].currentDirection != SnakeFragment::DIRECTION_LEFT) body[0].currentDirection = SnakeFragment::DIRECTION_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (body[0].currentDirection != SnakeFragment::DIRECTION_RIGHT) body[0].currentDirection = SnakeFragment::DIRECTION_LEFT;
	}
}

bool Snake::died()
{
	sf::Vector2u renderWindowSize = m_gameSetup->getRenderWindow()->getSize();

	if (body[0].getPosition().x < 0.f || body[0].getPosition().x > renderWindowSize.x) return true;
	if (body[0].getPosition().y < 0.f || body[0].getPosition().y > renderWindowSize.y) return true;

	for (int i = 1; i < body.size(); i++)
	{
		if (body[0].getGlobalBounds().contains(body[i].getPosition())) return true;
	}

	return false;
}

void Snake::reset()
{
	updateTime = 60;
	fruitSpawnTime = 420;
	updateTimeA = 0;
	fruitSpawnTimeA = 0;

	fruits.clear();
	body.clear();
	spawn();
	spawnFruit();
}

bool Snake::eaten()
{
	for (int i = 0; i < fruits.size(); i++)
	{
		if (body[0].getGlobalBounds().contains(fruits[i].getPosition()))
		{
			appendSnakeFragment();
			fruits.erase(fruits.begin() + i);

			return true;
		}
	}

	return false;
}

void Snake::appendSnakeFragment()
{
	SnakeFragment newSnakeFragment(m_fragmentSize, m_gameSetup->getResourceManager().getTexture("snakeTxt"));
	SnakeFragment lastSnakeFragment = body[body.size() - 1];

	switch (lastSnakeFragment.currentDirection)
	{
		case SnakeFragment::DIRECTION_UP:
			newSnakeFragment.setPosition(lastSnakeFragment.getPosition().x, lastSnakeFragment.getPosition().y + step);
			break;

		case SnakeFragment::DIRECTION_DOWN:
			newSnakeFragment.setPosition(lastSnakeFragment.getPosition().x, lastSnakeFragment.getPosition().y - step);
			break;

		case SnakeFragment::DIRECTION_RIGHT:
			newSnakeFragment.setPosition(lastSnakeFragment.getPosition().x - step, lastSnakeFragment.getPosition().y);
			break;

		case SnakeFragment::DIRECTION_LEFT:
			newSnakeFragment.setPosition(lastSnakeFragment.getPosition().x + step, lastSnakeFragment.getPosition().y);
			break;
	}

	newSnakeFragment.setSprite(SnakeFragment::SPRITE_TAIL);
	body.push_back(newSnakeFragment);
}

int Snake::getLength()
{
	return body.size();
}


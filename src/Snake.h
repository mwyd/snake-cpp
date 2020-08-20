#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <iostream>

#include "SnakeFragment.h"
#include "Fruit.h"
#include "State.h"
#include "Setup.h"

class Snake : public State
{
private:
	int step;
	sf::Text score;
	Setup* m_gameSetup;

	const int minUpdateTime = 20;
	const int maxUpdateTime = 200;

	float updateTime = 60;
	float fruitSpawnTime = 420;
	float updateTimeA = 0;
	float fruitSpawnTimeA = 0;

	sf::Vector2u m_fragmentSize;
	std::vector<Fruit> fruits;
	std::vector<SnakeFragment> body;
	std::function<void(float)> updater = [](float deltaTime) {};

public:
	Snake(sf::Vector2u fragmentSize, Setup* gameSetup);
	~Snake();

	void update(float deltaTime) override;
	void draw()	override;
	void eventHandler(sf::Event& event)	override;

	int getLength();
	void setArcadeUpdater();
	void setClassicUpdater();

private:
	void run();
	bool died();
	void reset();
	bool eaten();
	void spawn();
	void spawnFruit();
	void onKeyDown();
	void appendSnakeFragment();
};


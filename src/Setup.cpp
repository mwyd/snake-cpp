#include "Setup.h"

Setup::Setup() : renderWindow(nullptr)
{

}

Setup::~Setup()
{

}

StateMachine& Setup::getStateMachine()
{
	return stateMachine;
}

ResourceManager& Setup::getResourceManager()
{
	return resourceManager;
}

void Setup::setRenderWindow(sf::RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
}

sf::RenderWindow* Setup::getRenderWindow()
{
	return renderWindow;
}
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::loadTexture(std::string id, std::string path)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

	if (!texture->loadFromFile(path))
	{
		//error handle
	}

	textures.insert({ id, texture });
}

void ResourceManager::loadFont(std::string id, std::string path)
{
	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

	if (!font->loadFromFile(path))
	{
		//error handle
	}

	fonts.insert({ id, font });
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(std::string id)
{
	return textures[id];
}

std::shared_ptr<sf::Font> ResourceManager::getFont(std::string id)
{
	return fonts[id];
}
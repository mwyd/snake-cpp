#pragma once
#include <map>

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadTexture(std::string id, std::string path);
	void loadFont(std::string id, std::string path);

	std::shared_ptr<sf::Texture> getTexture(std::string id);
	std::shared_ptr<sf::Font> getFont(std::string id);

private:
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;
};


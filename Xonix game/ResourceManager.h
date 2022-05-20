#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>
//#include "loudingFillExeption.h"

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager& instance();

	const sf::Texture& getPicture(std::string picture);
	const std::unique_ptr<sf::Music>& getMusic(std::string sound);
	const sf::Font& getText(std::string font);

private:
	ResourceManager();
	ResourceManager(const ResourceManager&);

	std::map<std::string, sf::Texture> m_texture;
	std::map<std::string, std::unique_ptr<sf::Music>> m_music;
	std::map<std::string, sf::Font> m_text;

	sf::Texture createTexture(const std::string& picture);
	std::unique_ptr<sf::Music> createMusic(const std::string& sound);
	sf::Font createText(const std::string& font);










};

#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Object
{

public:
	Object(sf::Vector2f = { 0,0 });

	sf::Sprite getObject() const;
	//Checks crash with walls
	bool crashObjects(sf::Sprite, int) const;
	//Checks crash with cookies
	bool crashObjectsBorder(sf::Sprite, int) const;
	sf::Vector2f getPosition();
protected:
	sf::Sprite m_object;
	sf::Texture m_texture;

};

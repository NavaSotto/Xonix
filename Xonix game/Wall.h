#pragma once
#include "StaticObject.h"

class Wall :public StaticObject
{
public:
	Wall(sf::Vector2f = { 0,0 });
	virtual ~Wall();
};
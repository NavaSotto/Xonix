#pragma once
#include "StaticObject.h"

class Gift :public StaticObject
{
public:
	static int total;//count how much cookies we have
	static float m_speedIncrease;

	Gift(char c, sf::Vector2f = { 0,0 });
	virtual ~Gift();

	void createColor(char c);

};

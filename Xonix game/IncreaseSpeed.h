#pragma once
#include "Gift.h"

class IncreaseSpeed :public Gift
{
public:
	static float m_SpeedIncrease;

	IncreaseSpeed(char c, sf::Vector2f place = { 0,0 });
	virtual ~IncreaseSpeed();

};

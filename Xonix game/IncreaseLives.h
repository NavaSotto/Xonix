#pragma once
#include "Gift.h"

class IncreaseLives :public Gift
{
public:
	static float m_speedIncreased;

	IncreaseLives(char c, sf::Vector2f place = { 0,0 });
	virtual ~IncreaseLives();


};

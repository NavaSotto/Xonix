#pragma once
#include "Enemy.h"

class NormalEnemy :public Enemy
{
public:
	NormalEnemy(sf::Vector2f place, sf::Vector2i boardPosition);

	//Returns a value between 0 to 3 to know where to move to
	virtual int moving(Game&);
};
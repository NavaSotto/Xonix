#pragma once
#include "Enemy.h"

class SmartEnemy :public Enemy
{
public:
	SmartEnemy(sf::Vector2f place, sf::Vector2i boardPosition);
	virtual int moving(Game&);//return 0-3 where to move
};
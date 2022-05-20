#pragma once
#include "DynamicObject.h"

class Enemy :public DynamicObject
{
public:
	Enemy(sf::Vector2f place, sf::Vector2i boardPosition);

	//double dispatch 
	//collide active with active
	virtual void collide(DynamicObject*, Game&);
	virtual void collide(Player*, Game&);
	virtual void collide(Enemy*, Game&);
	//collide active with passive
	virtual void collide(StaticObject*, Game&, Board&, sf::Vector2f);

	virtual void cookieCrash(float, Game&) {};
	//Locates the ghost
	virtual void makePosition(Board &, Game&);
	void PutInPlace(int, Board &, Game&);
};

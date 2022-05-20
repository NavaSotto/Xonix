#pragma once
#include "Object.h"
#include "StaticObject.h"
#include "Wall.h"
#include "IncreaseSpeed.h"
#include "IncreaseLives.h"
#include "Gift.h"


class Enemy;
class Player;
class Game;
class Board;

class DynamicObject :public Object
{


public:
	//static value
	static float speed;//all the players have the same speed in the beginning.

					   //constructor
	DynamicObject(sf::Vector2f = { 0,0 }, sf::Vector2i boardPosition = { 0,0 });

	//set/get functions
	void setPosition(sf::Vector2f);
	float getSpeed() const;//get the current speed of the player
	virtual void setSpeed(float) {};//virtual function that change the speed only on the types pacmans
	int getLastPos() const;
	int getLastSide() const;

	//move
	virtual void move(float, Game&, Board&);
	virtual int moving(Game&) = 0;

	//collides
	virtual void collide(StaticObject*, Game&, Board&, sf::Vector2f) = 0;//collide active whith passive
																				//double dispatch 
	virtual void collide(DynamicObject*, Game&) = 0;
	virtual void collide(Player*, Game&) = 0;
	virtual void collide(Enemy*, Game&) = 0;
	//eat cookie
	virtual void cookieCrash(float, Game&) = 0;
	sf::Vector2i getBoardPosition();
	//lacating
	virtual void makePosition(Board &, Game&) = 0;

protected:
	float m_speed;//the speed of the player
	int m_lastPos = 0;//save the last change direction 
	int m_last_side = 0;//save from which side the player came to the wall
	sf::Vector2i m_boardPosition;
};

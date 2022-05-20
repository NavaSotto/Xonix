#pragma once
#include "DynamicObject.h"
#include <SFML/Audio.hpp>

class Player :public DynamicObject
{


public:
	Player(sf::Vector2f = { 0,0 }); //Default constructor

	int getLives() const;
	void setLives(int);

	//Collide of double dispatch - checks collide of active with active
	virtual void collide(DynamicObject*, Game&);
	virtual void collide(Player*, Game&);
	virtual void collide(Enemy*, Game&);

	//Checks collide of active with passive
	virtual void collide(StaticObject*, Game&, Board&, sf::Vector2f);

	//Locates the pacman as close to the center
	virtual void makePosition(Board &, Game&);

	int getScore() const;
	void setScore(int);
	virtual void setSpeed(float);

	//Returns a value between 0 to 3 to know where to move to
	virtual int moving(Game&);
	void move(sf::Keyboard::Key d, Board & board, std::vector<std::shared_ptr<DynamicObject>> enemy, Game& game);
	//A virtual check if crashed with cookie function
	virtual void cookieCrash(float, Game&);


protected:
	int m_lives;
	int m_score = 0;
	sf::Vector2i m_beginClose;
	sf::Vector2i m_endClose;
	
};


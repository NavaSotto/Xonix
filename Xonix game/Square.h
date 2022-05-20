#pragma once
#include "StaticObject.h"
#include "ResourceManager.h"

enum square_mode {CLOSE, RUN, ICE, EMPTY};

class Square : public StaticObject
{
public:
	Square(sf::Vector2f position, const sf::Vector2f sizeOfTexture, square_mode s);
	~Square();
	virtual void drawObject(sf::RenderWindow &window);
	void setSquare(square_mode);
	sf::Vector2f getPosition();
	square_mode getMode();
	bool getCover();
	void setCover(bool);
private:
	square_mode m_sMode;
	bool m_ifCover;

};


#include "Gift.h"
#include "Board.h"

int Gift::total = 0;  //counts how many cookies are there
float Gift::m_speedIncrease = 1;

Gift::Gift(char c, sf::Vector2f place) : StaticObject(place)
{
	m_texture = ResourceManager::instance().getPicture("increaseSpeed");
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
	total++;
}

Gift::~Gift()
{
	total--;
}


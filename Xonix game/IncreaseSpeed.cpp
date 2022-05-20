#include "IncreaseSpeed.h"
#include "Board.h"
#include <random>

float IncreaseSpeed::m_SpeedIncrease = (float)1.2;

IncreaseSpeed::IncreaseSpeed(char c, sf::Vector2f place) :Gift(c, place)
{
	int p = rand()%(2);
	if(p=0)
		m_texture = ResourceManager::instance().getPicture("increaseSpeed");
	else
		m_texture = ResourceManager::instance().getPicture("increaseScore");

	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

IncreaseSpeed::~IncreaseSpeed()
{
}


#include "IncreaseLives.h"
#include "Board.h"

float IncreaseLives::m_speedIncreased = (float)0.9;

IncreaseLives::IncreaseLives(char c, sf::Vector2f place) : Gift(c, place)
{


	
	m_texture = ResourceManager::instance().getPicture("increaseLives");
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

IncreaseLives::~IncreaseLives()
{
}



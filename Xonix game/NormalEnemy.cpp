#include "NormalEnemy.h"
#include "Game.h"

NormalEnemy::NormalEnemy(sf::Vector2f place, sf::Vector2i boardPosition) : Enemy(place, boardPosition)
{
	m_texture = ResourceManager::instance().getPicture("normalEnemy");

	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
	m_object.setPosition(place);

	//switch (color)
	//{
	//case 0:
	//	m_object.setColor(sf::Color::Red);//'%'
	//	break;
	//case 1:
	//	m_object.setColor(sf::Color::Green);//'T'
	//	break;
	//case 2:
	//	m_object.setColor(sf::Color::Yellow);//'G'-BLUE
	//	break;
	//case 3:
	//	m_object.setColor(sf::Color::Red);//'%'
	//	break;
	//default:
	//	break;
	//}
}

int NormalEnemy::moving(Game&)
{
	int x = random(25);
	if (x == 8)
		m_lastPos = (random(4));
	return m_lastPos;
}


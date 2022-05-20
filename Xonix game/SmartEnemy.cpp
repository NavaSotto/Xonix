#include "SmartEnemy.h"
#include "Game.h"

SmartEnemy::SmartEnemy(sf::Vector2f place, sf::Vector2i boardPosition) : Enemy(place, boardPosition)
{
	m_texture = ResourceManager::instance().getPicture("specialEnemy");
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
	m_object.setPosition(place);

	
}

//returns a moving value according to the pacmans location
int SmartEnemy::moving(Game& control)
{
	//an int is used in order to emphasise the little differences between him to the user pacman 
	if ((int)(m_boardPosition.y) > (int)(control.getPacman()->getBoardPosition().y))
		return 0;//up
	if ((int)(m_boardPosition.y) < (int)(control.getPacman()->getBoardPosition().y))
		return 1;//down
	if ((int)(m_boardPosition.x) > (int)(control.getPacman()->getBoardPosition().x))
		return 2;//left
	if ((int)(m_boardPosition.x) < (int)(control.getPacman()->getBoardPosition().x))
		return 3;//right
	return 4;
}


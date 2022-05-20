#include "Object.h"
#include "Board.h"
#include <stdlib.h>  
#include <math.h> 

Object::Object(sf::Vector2f place)
{
	m_object.setPosition(place);
}

sf::Sprite Object::getObject() const
{
	return m_object;
}

bool Object::crashObjects(sf::Sprite other, int side) const
{
	sf::Vector2f v1 = { (float)(m_object.getPosition().x + (m_object.getGlobalBounds().width / 2.f)),
		(float)(m_object.getPosition().y + (m_object.getGlobalBounds().height / 2.f)) };
	sf::Vector2f v2 = { (float)(other.getPosition().x + (other.getGlobalBounds().width / 2.f)),
		(float)(other.getPosition().y + (other.getGlobalBounds().height / 2.f)) };

	if (side == 2 || side == 3)  //left or right
		return (std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) <= Board::cubicle_size.x);

	if (side == 0 || side == 1)//up or down
		return(std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) <= Board::cubicle_size.y); //If the manhattan distance is samller than the cubicle size

	if (side == 4)
		return (std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) <= Board::cubicle_size.x && std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) <= Board::cubicle_size.y);
	return false;
}

//checks if crashed with an walls
bool Object::crashObjectsBorder(sf::Sprite other, int side) const
{
	sf::Vector2f v1 = { (float)(m_object.getPosition().x + (m_object.getGlobalBounds().width / 2.f)),
		(float)(m_object.getPosition().y + (m_object.getGlobalBounds().height / 2.f)) };
	sf::Vector2f v2 = { (float)(other.getPosition().x + (other.getGlobalBounds().width / 2.f)),
		(float)(other.getPosition().y + (other.getGlobalBounds().height / 2.f)) };

	if (side == 2 || side == 3)
		return (std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) < (Board::cubicle_size.x / 2.f));

	if (side == 0 || side == 1)//up or down
		return(std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) < ((Board::cubicle_size.y) / 2.f));

	if (side == 4)
		return (std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) < (Board::cubicle_size.x / 2.f) && std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2)) < ((Board::cubicle_size.y) / 2.f));
	return false;
}

sf::Vector2f Object::getPosition()
{
	return m_object.getPosition();
}


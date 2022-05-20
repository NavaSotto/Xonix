#include "Square.h"




Square::Square(sf::Vector2f position, const sf::Vector2f sizeOfTexture,square_mode s):
	StaticObject(position), m_sMode(s), m_ifCover(false)
{
	switch (s)
	{
	case ICE:
		m_object.setTexture(ResourceManager::instance().getPicture("ice"));
		break;
	case EMPTY:
		m_object.setTexture(ResourceManager::instance().getPicture("emptySquare"));
		break;
	default:
		break;
	}
	m_object.scale(sizeOfTexture.x / m_object.getGlobalBounds().width, sizeOfTexture.y / m_object.getGlobalBounds().height);
}


Square::~Square()
{
}



void Square::drawObject(sf::RenderWindow & window)
{
	window.draw(m_object);
}

void Square::setSquare(square_mode s)
{
	m_sMode = s;
	switch (s)
	{
	case CLOSE:
		m_object.setTexture(ResourceManager::instance().getPicture("closeSquare"));
		break;
	case RUN:
		m_object.setTexture(ResourceManager::instance().getPicture("runSquare"));
		break; 
	case ICE:
		m_object.setTexture(ResourceManager::instance().getPicture("ice"));
		break;
	case EMPTY:
		m_object.setTexture(ResourceManager::instance().getPicture("emptySquare"));
		break;
	default:
		break;
	}
	
}

sf::Vector2f Square::getPosition()
{
	return m_object.getPosition();
}

square_mode Square::getMode()
{
	return m_sMode;
}

bool Square::getCover()
{
	return m_ifCover;
}

void Square::setCover(bool b)
{
	m_ifCover = b;
}

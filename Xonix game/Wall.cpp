#include "Wall.h"
#include "Board.h"

Wall::Wall(sf::Vector2f place) :StaticObject(place)
{
	m_texture = ResourceManager::instance().getPicture("wall");
	m_object.setTexture(m_texture);
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });
}

Wall::~Wall()
{
}

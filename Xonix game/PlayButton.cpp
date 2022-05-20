#include "PlayButton.h"
#include "ResourceManager.h"
#include "Game.h"
PlayButton::PlayButton(const sf::Font& font, const sf::Vector2f position)
{
	m_button.setFont(font);
	m_button.setCharacterSize(55);
	m_button.setPosition(position);
	m_button.setFillColor(sf::Color::White);
	m_button.setOutlineColor(sf::Color::Red);
	m_button.setOutlineThickness(4);
	m_button.setString("PLAY");
}


PlayButton::~PlayButton()
{
}

void PlayButton::execute(sf::RenderWindow & m_window)
{
	ResourceManager::instance().getMusic("playMusic")->stop();
	Game m_c(m_window);
	m_c.manageGame();
}

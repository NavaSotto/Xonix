#include "ExitButton.h"



ExitButton::ExitButton(const sf::Font& font, const sf::Vector2f position)
{
	m_button.setFont(font);
	m_button.setCharacterSize(55);
	m_button.setPosition(position);
	m_button.setFillColor(sf::Color::White);
	m_button.setOutlineColor(sf::Color::Red);
	m_button.setOutlineThickness(4);
	m_button.setString("Exit");
}

ExitButton::~ExitButton()
{
}

void ExitButton::execute(sf::RenderWindow & m_window)
{
	m_window.close();
}

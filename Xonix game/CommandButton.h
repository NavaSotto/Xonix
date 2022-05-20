#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
class CommandButton
{
public:
	CommandButton();
	~CommandButton();

	virtual void execute(sf::RenderWindow &m_window) = 0;
	virtual void draw(sf::RenderWindow& window) { window.draw(m_button); };
	virtual void setFillColor(const sf::Color& color) { m_button.setFillColor(color); };
	virtual void setOtlineColor(const sf::Color& color)
	{
		m_button.setOutlineColor(color);
		m_button.setOutlineThickness(4);
	};

protected:
	sf::Text m_button;
	sf::Font m_font;
};
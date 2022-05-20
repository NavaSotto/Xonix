#pragma once
#include "CommandButton.h"
class HelpButton :public CommandButton
{
public:
	HelpButton(const sf::Font&, const sf::Vector2f position);
	~HelpButton();
	virtual void execute(sf::RenderWindow &m_window);
};
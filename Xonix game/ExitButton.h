#pragma once
#include "CommandButton.h"
class ExitButton :public CommandButton
{
public:
	ExitButton(const sf::Font&, const sf::Vector2f);
	~ExitButton();
	virtual void execute(sf::RenderWindow &m_window);
};


#pragma once
#include "CommandButton.h"

class PlayButton :public CommandButton
{
public:
	PlayButton(const sf::Font&, const sf::Vector2f position);
	~PlayButton();
	virtual void execute(sf::RenderWindow &m_window);
};
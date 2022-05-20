#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "CommandButton.h"

class Menu
{
public:
	Menu();
	~Menu() {};
	void openMenu();
	void manageMenu();
private:
	std::vector<std::unique_ptr<CommandButton>> m_option;
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Texture m_backTexture;
	sf::Sprite m_backSprite;
	int m_index;
	const int m_max = 3;
	void draw();
	void moveUp();
	void moveDown();
};

